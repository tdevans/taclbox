#ifndef UNITTESTDEPENDENCYPARSERDIALOG_H
#define UNITTESTDEPENDENCYPARSERDIALOG_H

#include <QDialog>
#include <QList>
#include <QTreeWidgetItem>
#include <QMap>
#include <QStringList>

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
    struct tTestFileStatus
    {
        QString filename;
        bool testRun;
        bool testPass;
    };

    Ui::UnitTestDependencyParserDialog *ui;
    QMap<QString, QList<tTestFileStatus>> mExpectTestFileMap;

    void refreshTable();

private slots:
};

#endif // UNITTESTDEPENDENCYPARSERDIALOG_H
