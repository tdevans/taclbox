#include "unittesthdlparserdialog.h"
#include "ui_unittesthdlparserdialog.h"
#include <QCoreApplication>
#include <QDir>
#include <QStringList>
#include <QDirIterator>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QFile>
#include <QBrush>
#include <QColor>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include "hdlparserentitydefinition.h"
#include "hdlparserarchitecturedefinition.h"

UnitTestHdlParserDialog::UnitTestHdlParserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UnitTestHdlParserDialog)
{
    ui->setupUi(this);

    connect(ui->runButton, &QPushButton::clicked, this, &UnitTestHdlParserDialog::runTests);
    connect(ui->testFileTree, &QTreeWidget::customContextMenuRequested, this, &UnitTestHdlParserDialog::getTreeContextMenu);

    QDir dependencyParserTestDir(QCoreApplication::applicationDirPath() + QDir::separator() + ".." + QDir::separator() + "test" + QDir::separator() + "data" + QDir::separator() + "hdl_parser");
    QDirIterator expectIterator(dependencyParserTestDir.canonicalPath(), QStringList() << "*.json", QDir::Files, QDirIterator::Subdirectories);

    while (expectIterator.hasNext())
    {
        expectIterator.next();
        QFileInfo expectFileInfo = expectIterator.fileInfo();
        QDirIterator testFileIterator(expectFileInfo.absolutePath(), QStringList() << "*.vhd" << "*.v" << "*.sv", QDir::Files, QDirIterator::NoIteratorFlags);

        TestCase c;
        ExpectFile ef = parseExpectFile(expectFileInfo.absoluteFilePath());

        c.expectFile = ef;

        while (testFileIterator.hasNext())
        {
            testFileIterator.next();
            QFileInfo testFileInfo = testFileIterator.fileInfo();
            TestFile f;
            f.filePath = testFileInfo.absoluteFilePath();
            f.testRun = false;
            f.testPass = false;
            c.testFiles.append(f);
        }

        mTestCases.append(c);
    }

    refreshTable();
}

UnitTestHdlParserDialog::~UnitTestHdlParserDialog()
{
    delete ui;
}

void UnitTestHdlParserDialog::refreshTable()
{
    ui->testFileTree->clear();
    for (int i = 0; i < mTestCases.size(); ++i)
    {
        TestCase& tc = mTestCases[i];
        QTreeWidgetItem* e = new QTreeWidgetItem(QStringList() << tc.expectFile.filePath << "");
        e->setData(0, Qt::UserRole, QVariant(i)); // We put the test case ID into the data field of column 0 so we can get back to the test case from the GUI information

        bool someRun = false;
        bool allRun = true;
        bool allPass = true;
        for (int j = 0; j < tc.testFiles.size(); ++j)
        {
            TestFile& tf = tc.testFiles[j];
            QTreeWidgetItem* t = new QTreeWidgetItem();

            t->setText(0, tf.filePath);
            t->setData(0, Qt::UserRole, j); // Put the test file ID into the data field of column 0 so we can get back to the test file object that made this GUI object

            if (tf.testRun)
            {
                someRun = true;
                if (tf.testPass)
                {
                    t->setText(1, "PASS");
                    t->setForeground(1, QBrush(Qt::white));
                    t->setBackground(1, QBrush(Qt::darkGreen));
                }
                else
                {
                    allPass = false;
                    t->setText(1, "FAIL");
                    t->setForeground(1, QBrush(Qt::white));
                    t->setBackground(1, QBrush(Qt::darkRed));
                }
            }
            else
            {
                allRun = false;
                t->setText(1, "-");
                t->setForeground(1, QBrush(Qt::black));
                t->setBackground(1, QBrush(Qt::white));
            }

            e->addChild(t);
        }

        if (tc.expectFile.parseError)
        {
            e->setText(1, "PARSE ERROR");
            e->setForeground(1, QBrush(Qt::white));
            e->setBackground(1, QBrush(Qt::darkRed, Qt::Dense2Pattern));
        }
        else
        {
            if (someRun)
            {
                if (allPass)
                {
                    e->setText(1, "PASS");
                    if (allRun)
                    {
                        e->setForeground(1, QBrush(Qt::white));
                        e->setBackground(1, QBrush(Qt::darkGreen));
                    }
                    else
                    {
                        e->setForeground(1, QBrush(Qt::white));
                        e->setBackground(1, QBrush(Qt::darkGreen, Qt::Dense3Pattern));
                    }
                }
                else
                {
                    e->setText(1, "FAIL");
                    e->setForeground(1, QBrush(Qt::white));
                    e->setBackground(1, QBrush(Qt::darkRed));
                }
            }
        }
        ui->testFileTree->addTopLevelItem(e);
    }
    ui->testFileTree->resizeColumnToContents(0);
}

UnitTestHdlParserDialog::ExpectFile UnitTestHdlParserDialog::parseExpectFile(QString filePath)
{
    ExpectFile expectFile;

    expectFile.filePath = filePath;
    expectFile.parseError = false;

    QFile f(filePath);
    if (f.open(QIODevice::ReadOnly))
    {
        QByteArray b = f.readAll();
        QJsonParseError dError;
        QJsonDocument d = QJsonDocument::fromJson(b, &dError);
        f.close();

        if (d.isNull())
        {
            ui->testResultsTextEdit->appendHtml(QString("<span style=\"color: red\">Error: Unable to parse expect file %1.</span>").arg(filePath));
            ui->testResultsTextEdit->appendHtml(QString("<span style=\"color: red\">%1</span>").arg(dError.errorString()));
            expectFile.parseError = true;
        }
        else
        {
            if (d.isObject())
            {
                QJsonObject o = d.object();
                if (o.contains("defines") && o["defines"].isObject())
                {
                    QJsonObject d = o["defines"].toObject();
                    if (d.contains("entity") && d["entity"].isArray())
                    {
                        QJsonArray a = d["entity"].toArray();
                        for (auto e : a)
                        {
                            if (e.isObject())
                            {
                                QJsonObject f = e.toObject();
                                if (f.contains("name"))
                                {
                                    ExpectFileEntityDefinition g;
                                    g.name = f["name"].toString();

                                    if (f.contains("generics") && f["generics"].isArray())
                                    {
                                        QJsonArray h = f["generics"].toArray();
                                        for (auto i : h)
                                        {
                                            if (i.isObject())
                                            {
                                                QJsonObject j = i.toObject();
                                                if (j.contains("name") && j.contains("type"))
                                                {
                                                    ExpectFileGenericDefinition k;
                                                    k.name = j["name"].toString();
                                                    k.type = j["type"].toString();
                                                    g.generics.append(k);
                                                }
                                            }
                                        }
                                    }

                                    if (f.contains("ports") && f["ports"].isArray())
                                    {
                                        QJsonArray h = f["ports"].toArray();
                                        for  (auto i : h)
                                        {
                                            if (i.isObject())
                                            {
                                                QJsonObject j = i.toObject();
                                                if (j.contains("name") && j.contains("type"))
                                                {
                                                    ExpectFilePortDefinition k;
                                                    k.name = j["name"].toString();
                                                    k.type = j["type"].toString();
                                                    if (j.contains("dir"))
                                                    {
                                                        k.dir = j["dir"].toString().toLower();
                                                    }
                                                    else
                                                    {
                                                        k.dir = "in";
                                                    }
                                                    g.ports.append(k);
                                                }
                                            }
                                        }
                                    }
                                    expectFile.entityDefinitions.append(g);
                                }
                            }
                        }
                    }

                    if (d.contains("architecture") && d["architecture"].isArray())
                    {
                        QJsonArray a = d["architecture"].toArray();
                        for (auto e : a)
                        {
                            if (e.isObject())
                            {
                                QJsonObject f = e.toObject();
                                if (f.contains("name") && f.contains("entity"))
                                {
                                    ExpectFileArchitectureDefinition g;
                                    g.name = f["name"].toString();
                                    g.entityName = f["entity"].toString();

                                    if (f.contains("signals") && f["signals"].isArray())
                                    {
                                        QJsonArray h = f["signals"].toArray();
                                        for (auto i : h)
                                        {
                                            if (i.isObject())
                                            {
                                                QJsonObject j = i.toObject();
                                                if (j.contains("name") && j.contains("type"))
                                                {
                                                    ExpectFileSignalDefinition k;
                                                    k.name = j["name"].toString();
                                                    k.typeName = j["type"].toString();
                                                    g.sigs.append(k);
                                                }
                                            }
                                        }
                                    }

                                    if (f.contains("types") && f["types"].isArray())
                                    {
                                        QJsonArray h = f["types"].toArray();
                                        for (auto i : h)
                                        {
                                            if (i.isObject())
                                            {
                                                QJsonObject j = i.toObject();
                                                if (j.contains("name"))
                                                {
                                                    ExpectFileTypeDefinition k;
                                                    k.name = j["name"].toString();

                                                    if (j.contains("enum") && j["enum"].isArray())
                                                    {
                                                        QJsonArray l = j["enum"].toArray();
                                                        for (auto m : l)
                                                        {
                                                            if (m.isString())
                                                            {
                                                                k.enumValues.append(m.toString());
                                                            }
                                                        }
                                                    }

                                                    g.types.append(k);
                                                }
                                            }
                                        }
                                    }

                                    expectFile.architectureDefinitions.append(g);
                                }
                            }
                        }
                    }

                    if (d.contains("packageHeader"))
                    {
                        QJsonArray a = d["packageHeader"].toArray();
                        for (auto e : a)
                        {
                            if (e.isObject())
                            {
                                QJsonObject f = e.toObject();
                                if (f.contains("name"))
                                {
                                    ExpectFilePackageHeaderDefinition g;
                                    g.name = f["name"].toString();
                                    expectFile.packageHeaderDefinitions.append(g);
                                }
                            }
                        }
                    }

                    if (d.contains("packageBody"))
                    {
                        QJsonArray a = d["packageBody"].toArray();
                        for (auto e : a)
                        {
                            if (e.isObject())
                            {
                                QJsonObject f = e.toObject();
                                if (f.contains("name"))
                                {
                                    ExpectFilePackageBodyDefinition g;
                                    g.name = f["name"].toString();
                                    expectFile.packageBodyDefinitions.append(g);
                                }
                            }
                        }
                    }
                }

                if (o.contains("depends") && o["depends"].isObject())
                {
                    QJsonObject d = o["depends"].toObject();
                    if (d.contains("library"))
                    {
                        QJsonArray a = d["library"].toArray();
                        for (auto e : a)
                        {
                            if (e.isObject())
                            {
                                QJsonObject f = e.toObject();
                                if (f.contains("name"))
                                {
                                    ExpectFileLibraryDependency g;
                                    g.name = f["name"].toString();
                                    expectFile.libraryDependencies.append(g);
                                }
                            }
                        }
                    }

                    if (d.contains("package"))
                    {
                        QJsonArray a = d["package"].toArray();
                        for (auto e : a)
                        {
                            if (e.isObject())
                            {
                                QJsonObject f = e.toObject();
                                if (f.contains("name") && f.contains("library"))
                                {
                                    ExpectFilePackageDependency g;
                                    g.name = f["name"].toString();
                                    g.libraryName = f["library"].toString();
                                    expectFile.packageDependencies.append(g);
                                }
                            }
                        }
                    }

                    if (d.contains("module"))
                    {
                        QJsonArray a = d["module"].toArray();
                        for (auto e : a)
                        {
                            if (e.isObject())
                            {
                                QJsonObject f = e.toObject();
                                if (f.contains("instanceName") && f.contains("entityName"))
                                {
                                    ExpectFileModuleDependency g;
                                    g.instanceName = f["instanceName"].toString();
                                    g.entityName = f["entityName"].toString();

                                    if (f.contains("architectureName"))
                                    {
                                        g.architectureName = f["architectureName"].toString();
                                    }

                                    if (f.contains("libraryName"))
                                    {
                                        g.libraryName = f["libraryName"].toString();
                                    }

                                    expectFile.moduleDependencies.append(g);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return expectFile;
}

void UnitTestHdlParserDialog::runTestCase(TestCase& tc)
{
    if (!tc.expectFile.parseError)
    {
        ui->testResultsTextEdit->appendPlainText(QString("Running test case for expect file: %1").arg(tc.expectFile.filePath));
        for (auto& tf : tc.testFiles)
        {
            runTestFile(tf, tc.expectFile);
        }
    }
}

void UnitTestHdlParserDialog::runTestFile(TestFile& tf, ExpectFile& ef)
{
    QFile f(tf.filePath);
    if (f.open(QIODevice::ReadOnly))
    {
        QString txt = f.readAll();
        f.close();

        ui->testResultsTextEdit->appendPlainText(QString("Parsing %1...").arg(tf.filePath));

        // We'll set this to fail if any of the individual tests fails
        bool pass = true;

        // Parse the file to get the entities it defines
        QList<HdlParserEntityDefinition> e = HdlParserEntityDefinition::parseText(QStringRef(&txt), tf.filePath, 1);

        // Check that all the entities we find are in the list of entities we expected to find
        for (const auto& pe : e)
        {
            ui->testResultsTextEdit->appendPlainText(QString("Found entity %1 on line %2").arg(pe.name()).arg(pe.lineNum()));

            // Make sure this entity is supposed to exist
            bool entityFound = false;
            const ExpectFileEntityDefinition* matchingEntity;
            for (const auto& ed : ef.entityDefinitions)
            {
                if (pe.name() == ed.name)
                {
                    entityFound = true;
                    matchingEntity = &ed;
                    break;
                }
            }

            if (!entityFound)
            {
                ui->testResultsTextEdit->appendHtml(QString("<span style=\"color: red;\">Error: Found entity %1 in the test file, but it was not expected.</span>").arg(pe.name()));
                pass = false;
            }

            // Make sure the generics match what is expected
            ui->testResultsTextEdit->appendPlainText("\tGenerics:");
            for (const auto& g : pe.generics())
            {
                ui->testResultsTextEdit->appendPlainText(QString("\t\tname=%1, type=%2 @ line=%3").arg(g.name(), g.type()).arg(g.lineNum()));
                if (entityFound)
                {
                    bool genericFound = false;
                    for (const auto& eg : matchingEntity->generics)
                    {
                        if ((eg.name == g.name()) && (eg.type == g.type()))
                        {
                            genericFound = true;
                            break;
                        }
                    }
                    if (!genericFound)
                    {
                        ui->testResultsTextEdit->appendHtml(QString("<span style=\"color: red;\">Error: Found generic %1 in the test file, but it was not expected.</span>").arg(g.name()));
                        pass = false;
                    }
                }
            }

            // Make sure all the expected generics are there
            if (entityFound)
            {
                for (const auto& eg : matchingEntity->generics)
                {
                    bool genericFound = false;
                    for (const auto& g : pe.generics())
                    {
                        if ((eg.name == g.name()) && eg.type == g.type())
                        {
                            genericFound = true;
                            break;
                        }
                    }
                    if (!genericFound)
                    {
                        ui->testResultsTextEdit->appendHtml(QString("<span style=\"color: red;\">Error: Expected to find generic %1 with type %2, but did not.</span>").arg(eg.name, eg.type));
                        pass = false;
                    }
                }
            }

            ui->testResultsTextEdit->appendPlainText("\tPorts:");

            // Make sure the ports we found are expected
            for (const auto& p : pe.ports())
            {
                ui->testResultsTextEdit->appendPlainText(QString("\t\tname=%1, direction=%2, type=%3 @ line=%4").arg(p.name(), p.dirString(), p.type()).arg(p.lineNum()));

                if (entityFound)
                {
                    bool portFound = false;
                    for (const auto& ep : matchingEntity->ports)
                    {
                        if ((ep.name == p.name()) && (ep.type == p.type()) && (ep.dir == p.dirString().toLower()))
                        {
                            portFound = true;
                            break;
                        }
                    }
                    if (!portFound)
                    {
                        ui->testResultsTextEdit->appendHtml(QString("<span style=\"color: red;\">Error: Found port %1 in the test file, but it was not expected.</span>").arg(p.name()));
                        pass = false;
                    }
                }
            }

            // Make sure all the expected ports are there
            if (entityFound)
            {
                for (const auto& ep : matchingEntity->ports)
                {
                    bool portFound = false;
                    for (const auto& p : pe.ports())
                    {
                        if ((ep.name == p.name()) && (ep.type == p.type()) && (ep.dir == p.dirString().toLower()))
                        {
                            portFound = true;
                            break;
                        }
                    }
                    if (!portFound)
                    {
                        ui->testResultsTextEdit->appendHtml(QString("<span style=\"color: red;\">Error: Expected to find port %1 with direction %2 and type %3, but did not.</span>").arg(ep.name, ep.dir, ep.type));
                        pass = false;
                    }
                }
            }
        }

        // Check that we found all the entities we expected to find
        for (const auto& ed : ef.entityDefinitions)
        {
            bool found = false;
            for (const auto& pe : e)
            {
                if (pe.name() == ed.name)
                {
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                ui->testResultsTextEdit->appendHtml(QString("<span style=\"color: red;\">Error: Did not find expected entity %1.</span>").arg(ed.name));
                pass = false;
            }
        }


        // Parse the file to get the architectures it defines
        QList<HdlParserArchitectureDefinition> a = HdlParserArchitectureDefinition::parseText(QStringRef(&txt), tf.filePath, 1);

        // Make sure all the architectures we find in the file are ones we expected
        for (const auto& pa : a)
        {
            ui->testResultsTextEdit->appendPlainText(QString("Found architecture %1 for entity %2 at line %3").arg(pa.name(), pa.entityName()).arg(pa.lineNum()));
            bool architectureFound = false;
            const ExpectFileArchitectureDefinition* matchingArchitecture;
            for (const auto& ad : ef.architectureDefinitions)
            {
                if ((pa.name() == ad.name) && (pa.entityName() == ad.entityName))
                {
                    architectureFound = true;
                    matchingArchitecture = &ad;
                    break;
                }
            }

            if (!architectureFound)
            {
                ui->testResultsTextEdit->appendHtml(QString("<span style=\"color: red\">Error: Found architecture %1 for entity %2 in the test file, but it was not expected.</span>").arg(pa.name(), pa.entityName()));
                pass = false;
            }

            // Check that any type definitions detected are ones we expected
            ui->testResultsTextEdit->appendPlainText("\tTypes:");
            for (const auto& t : pa.types())
            {
                switch (t.category())
                {
                case HdlParserTypeDefinition::ENUM:
                    ui->testResultsTextEdit->appendPlainText(QString("\t\tname=%1, enum= @ line=%2").arg(t.name()).arg(t.lineNum()));
                    for (const auto& e : t.enumValues())
                    {
                        ui->testResultsTextEdit->appendPlainText(QString("\t\t\t%1").arg(e));
                    }
                    break;

                case HdlParserTypeDefinition::SCALAR:
                    ui->testResultsTextEdit->appendPlainText(QString("\t\tname=%1, left=%2, right=%3, descending=%4 @ line=%5").arg(t.name()).arg(t.rangeLeft()).arg(t.rangeRight()).arg(t.rangeDescending()).arg(t.lineNum()));
                    break;
                }

                if (architectureFound)
                {
                    bool typeFound = false;
                    for (const auto& et : matchingArchitecture->types)
                    {
                        if (et.name == t.name())
                        {
                            typeFound = true;

                            if (!t.enumValues().isEmpty() && !et.enumValues.isEmpty())
                            {
                                if (t.enumValues().size() == et.enumValues.size())
                                {
                                    for (const auto& ev : t.enumValues())
                                    {
                                        if (!et.enumValues.contains(ev))
                                        {
                                            ui->testResultsTextEdit->appendHtml(QString("<span style=\"color: red;\">Error: Enum type %1 has value %2 that was not in the list of expected values.</span>").arg(t.name()).arg(ev));
                                            pass = false;
                                        }
                                    }
                                }
                                else
                                {
                                    ui->testResultsTextEdit->appendHtml(QString("<span style=\"color: red;\">Error: Parsed type %1 with %2 enum values, but expected %3 enum values.</span>").arg(t.name()).arg(t.enumValues().size()).arg(et.enumValues.size()));
                                    pass = false;
                                }
                            }
                            break;
                        }
                    }

                    if (!typeFound)
                    {
                        ui->testResultsTextEdit->appendHtml(QString("<span style=\"color: red;\">Error: Found type %1 in the test file, but it was not expected.</span>").arg(t.name()));
                        pass = false;
                    }
                }
            }

            // Check that any signals we detected are signals we expected
            ui->testResultsTextEdit->appendPlainText("\tSignals:");
            for (const auto& s : pa.sigs())
            {
                ui->testResultsTextEdit->appendPlainText(QString("\t\tname=%1, type=%2 @ line=%3").arg(s.name(), s.typeName()).arg(s.lineNum()));
                if (architectureFound)
                {
                    bool signalFound = false;
                    for (const auto& es : matchingArchitecture->sigs)
                    {
                        if ((es.name == s.name()) && (es.typeName == s.typeName()))
                        {
                            signalFound = true;
                            break;
                        }
                    }
                    if (!signalFound)
                    {
                        ui->testResultsTextEdit->appendHtml(QString("<span style=\"color: red;\">Error: Found signal %1 in the test file, but it was not expected.</span>").arg(s.name()));
                        pass = false;
                    }
                }
            }
        }

        // Make sure we found all the architectures we were expecting to find
        for (const auto& ad : ef.architectureDefinitions)
        {
            bool architectureFound = false;
            for (const auto& pa : a)
            {
                if ((pa.name() == ad.name) && (pa.entityName() == ad.entityName))
                {
                    architectureFound = true;
                    break;
                }
            }

            if (!architectureFound)
            {
                ui->testResultsTextEdit->appendHtml(QString("<span style=\"color: red\">Error: Did not find expected architecture %1 for entity %2.</span>").arg(ad.name, ad.entityName));
                pass = false;
            }
        }

        tf.testRun = true;
        tf.testPass = pass;
        ui->testResultsTextEdit->appendPlainText("\n");
    }

    refreshTable();
}

void UnitTestHdlParserDialog::runTests()
{
    for (auto& tc : mTestCases)
    {
        runTestCase(tc);
    }
}

void UnitTestHdlParserDialog::runTestCaseFromContextMenu()
{
    if ((ctxTestCase >= 0) && (ctxTestCase < mTestCases.size()))
    {
        TestCase& tc = mTestCases[ctxTestCase];
        runTestCase(tc);
    }
}

void UnitTestHdlParserDialog::runTestFileFromContextMenu()
{
    if ((ctxTestCase >= 0) && (ctxTestCase < mTestCases.size()))
    {
        TestCase& tc = mTestCases[ctxTestCase];
        if ((ctxTestFile >= 0) && (ctxTestFile < tc.testFiles.size()))
        {
            TestFile& tf = tc.testFiles[ctxTestFile];
            runTestFile(tf, tc.expectFile);
        }
    }
}


void UnitTestHdlParserDialog::getTreeContextMenu(const QPoint &pos)
{
    QTreeWidgetItem* clickedItem = ui->testFileTree->itemAt(pos);
    QAction* a = new QAction();

    if (clickedItem->parent())
    {
        a->setText("Run File");
        ctxTestCase = clickedItem->parent()->data(0, Qt::UserRole).toInt();
        ctxTestFile = clickedItem->data(0, Qt::UserRole).toInt();
        connect(a, &QAction::triggered, this, &UnitTestHdlParserDialog::runTestFileFromContextMenu);
    }
    else
    {
        a->setText("Run Test Case");
        ctxTestCase = clickedItem->data(0, Qt::UserRole).toInt();
        connect(a, &QAction::triggered, this, &UnitTestHdlParserDialog::runTestCaseFromContextMenu);
    }

    QMenu m;
    m.addAction(a);
    m.exec(ui->testFileTree->mapToGlobal(pos));
}
