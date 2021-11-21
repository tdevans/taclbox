#ifndef UNITTESTHDLPARSERDIALOG_H
#define UNITTESTHDLPARSERDIALOG_H

#include <QDialog>
#include <QList>
#include <QMap>
#include <QTreeWidgetItem>

namespace Ui {
class UnitTestHdlParserDialog;
}

class UnitTestHdlParserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UnitTestHdlParserDialog(QWidget *parent = nullptr);
    ~UnitTestHdlParserDialog();

private:
    Ui::UnitTestHdlParserDialog *ui;

    struct ExpectFileGenericDefinition
    {
        QString name;
        QString type;
    };

    struct ExpectFilePortDefinition
    {
        QString name;
        QString dir;
        QString type;
    };

    struct ExpectFileEntityDefinition
    {
        QString name;
        QList<ExpectFileGenericDefinition> generics;
        QList<ExpectFilePortDefinition> ports;
    };

    struct ExpectFileArrayRange
    {
        bool unconstrained;
        QString type;
        int left;
        int right;
        bool descending;
    };

    struct ExpectFileTypeDefinition
    {
        QString name;
        QStringList enumValues;
        QString arrayType;
        QList<ExpectFileArrayRange> arrayDimensions;
        double rangeLeft;
        double rangeRight;
        bool rangeDescending;
    };

    struct ExpectFileSignalDefinition
    {
        QString name;
        QString typeName;
    };

    struct ExpectFileArchitectureDefinition
    {
        QString name;
        QString entityName;
        QList<ExpectFileTypeDefinition> types;
        QList<ExpectFileSignalDefinition> sigs;
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
        bool parseError;
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

#endif // UNITTESTHDLPARSERDIALOG_H
