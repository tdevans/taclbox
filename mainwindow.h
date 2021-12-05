#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QList>
#include <QAction>

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

    QList<QAction*> mRecentProjectActions;

    void refreshRecentProjects();
    void updateProject();
    bool checkQuit();

private slots:
    void openProject(QString prjFile);
    void openRecentProject();
    void openProjectDialog();
    void closeProject();
    void openUnitTestDependencyParser();
};

#endif // MAINWINDOW_H
