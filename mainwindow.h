#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include "projectmanager.h"
#include "projectsummarywidget.h"
#include "sourcemanager.h"
#include "preferencesmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(PreferencesManager* preferencesManager, ProjectManager* projectManager, SourceManager* sourceManager, QWidget *parent = nullptr);
    ~MainWindow();

protected:
    virtual void closeEvent(QCloseEvent* event) override;

private:
    Ui::MainWindow *ui;
    ProjectManager* mProjectManager;
    SourceManager* mSourceManager;
    PreferencesManager* mPreferencesManager;

    ProjectSummaryWidget* mProjectSummaryTab;

    QTreeWidgetItem* mSourceFilesTreeWidgetItem;
    QTreeWidgetItem* mTestbenchFilesTreeWidgetItem;

    void updateProject();
    bool checkQuit();

private slots:
    void openProject();
    void openUnitTestDependencyParser();
};

#endif // MAINWINDOW_H
