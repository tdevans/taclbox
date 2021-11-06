#ifndef UNITTESTDEPENDENCYPARSERDIALOG_H
#define UNITTESTDEPENDENCYPARSERDIALOG_H

#include <QDialog>
#include <QList>

namespace Ui {
class UnitTestDependencyParserDialog;
}

class UnitTestDependencyParserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UnitTestDependencyParserDialog(QWidget *parent = nullptr);
    ~UnitTestDependencyParserDialog();

private:
    Ui::UnitTestDependencyParserDialog *ui;

    struct ExpectFileEntityDefinition
    {
        QString name;
    };

    struct ExpectFileArchitectureDefinition
    {
        QString name;
        QString entityName;
    };

    struct ExpectFilePackageHeaderDefinition
    {
        QString name;
    };

    struct ExpectFilePackageBodyDefinition
    {
        QString name;
    };

    struct ExpectFileLibraryDependency
    {
        QString name;
    };

    struct ExpectFilePackageDependency
    {
        QString name;
        QString libraryName;
    };

    struct ExpectFileModuleDependency
    {
        QString libraryName;
        QString entityName;
        QString architectureName;
        QString instanceName;
    };

    struct ExpectFile
    {
        QString filePath;
        QList<ExpectFileEntityDefinition> entityDefinitions;
        QList<ExpectFileArchitectureDefinition> architectureDefinitions;
        QList<ExpectFilePackageHeaderDefinition> packageHeaderDefinitions;
        QList<ExpectFilePackageBodyDefinition> packageBodyDefinitions;
        QList<ExpectFileLibraryDependency> libraryDependencies;
        QList<ExpectFilePackageDependency> packageDependencies;
        QList<ExpectFileModuleDependency> moduleDependencies;
    };

    struct TestFile
    {
        QString filePath;
        bool testRun;
        bool testPass;
    };

    struct TestCase
    {
        ExpectFile expectFile;
        QList<TestFile> testFiles;
    };

    QList<TestCase> mTestCases;

    // Used to pass context menu information to slots
    int ctxTestCase;
    int ctxTestFile;

    void refreshTable();
    ExpectFile parseExpectFile(QString filePath);
    void runTestCase(TestCase& tc);
    void runTestFile(TestFile& tf, ExpectFile& ef);

private slots:
    void runTests();
    void runTestCaseFromContextMenu();
    void runTestFileFromContextMenu();
    void getTreeContextMenu(const QPoint& pos);
};

#endif // UNITTESTDEPENDENCYPARSERDIALOG_H
