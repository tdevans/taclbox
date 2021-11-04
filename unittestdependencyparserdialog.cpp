#include "unittestdependencyparserdialog.h"
#include "ui_unittestdependencyparserdialog.h"
#include <QCoreApplication>
#include <QDir>
#include <QStringList>
#include <QDirIterator>
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
        mExpectTestFileMap.insert(expectFileInfo.absoluteFilePath(), QList<tTestFileStatus>());
        QDirIterator testFileIterator(expectFileInfo.absolutePath(), QStringList() << "*.vhd", QDir::Files, QDirIterator::NoIteratorFlags);
        while (testFileIterator.hasNext())
        {
            testFileIterator.next();
            QFileInfo testFileInfo = testFileIterator.fileInfo();
            mExpectTestFileMap[expectFileInfo.absoluteFilePath()].append({testFileInfo.absoluteFilePath(), false, false});

        }
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
    for (auto it = mExpectTestFileMap.begin(); it != mExpectTestFileMap.end(); ++it)
    {
        QTreeWidgetItem* e = new QTreeWidgetItem(QStringList() << it.key() << "");

        for (auto jt = it.value().begin(); jt != it.value().end(); ++jt)
        {
            QStringList cols;

            cols << (*jt).filename;
            if ((*jt).testRun)
            {
                if ((*jt).testPass)
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
