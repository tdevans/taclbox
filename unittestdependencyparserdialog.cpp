#include "unittestdependencyparserdialog.h"
#include "ui_unittestdependencyparserdialog.h"
#include <QCoreApplication>
#include <QDir>
#include <QStringList>
#include <QDirIterator>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDebug>


UnitTestDependencyParserDialog::UnitTestDependencyParserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UnitTestDependencyParserDialog)
{
    ui->setupUi(this);

    QDir dependencyParserTestDir(QCoreApplication::applicationDirPath() + QDir::separator() + ".." + QDir::separator() + "test" + QDir::separator() + "data" + QDir::separator() + "dependency_parser");
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

UnitTestDependencyParserDialog::~UnitTestDependencyParserDialog()
{
    delete ui;
}

void UnitTestDependencyParserDialog::refreshTable()
{
    ui->testFileTree->clear();
    for (const auto& tc : mTestCases)
    {
        QTreeWidgetItem* e = new QTreeWidgetItem(QStringList() << tc.expectFile.filePath << "");

        for (const auto& tf : tc.testFiles)
        {
            QStringList cols;

            cols << tf.filePath;
            if (tf.testRun)
            {
                if (tf.testPass)
                {
                    cols << "PASS";
                }
                else
                {
                    cols << "FAIL";
                }
            }
            else
            {
                cols << "-";
            }

            QTreeWidgetItem* t = new QTreeWidgetItem(cols);
            e->addChild(t);
        }

        ui->testFileTree->addTopLevelItem(e);
    }
    ui->testFileTree->expandAll();
    ui->testFileTree->resizeColumnToContents(0);
}

UnitTestDependencyParserDialog::ExpectFile UnitTestDependencyParserDialog::parseExpectFile(QString filePath)
{
    ExpectFile expectFile;

    expectFile.filePath = filePath;

    QFile f(filePath);
    if (f.open(QIODevice::ReadOnly))
    {
        QJsonDocument d = QJsonDocument::fromJson(f.readAll());
        f.close();

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

    return expectFile;
}
