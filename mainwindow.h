#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QList>
#include <QAction>
#include <QMap>

#include "projectmanager.h"
#include "projectsummarywidget.h"
#include "preferencesmanager.h"
#include "hdlparserlibrary.h"
#include "hdlfiletreewidgetitem.h"
#include "texteditorwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(PreferencesManager& preferencesManager, ProjectManager& projectManager, QWidget *parent = nullptr);
    ~MainWindow();

protected:
    virtual void closeEvent(QCloseEvent* event) override;

private:
    Ui::MainWindow *ui;
    ProjectManager& mProjectManager;
    PreferencesManager& mPreferencesManager;

    ProjectSummaryWidget* mProjectSummaryTab;

    QTreeWidgetItem* mSourceFilesTreeWidgetItem;
    QTreeWidgetItem* mTestbenchFilesTreeWidgetItem;

    QList<QAction*> mRecentProjectActions;

    void refreshRecentProjects();
    void updateProject();
    bool checkQuit();

    // We take a QList of library objects which share the same name
    // This is so that if the parser found multiple declarations of
    // the same library, we can display error information appropriately.
    void addLibraryToStructure(QList<HdlParserLibrary>& lib);
    void addPackageToStructure(QTreeWidgetItem* lib, QList<HdlParserPackageHeaderDefinition>& pkg);

private slots:
    void openProject(QString prjFile);
    void openRecentProject();
    void openProjectDialog();
    void closeProject();
    void openUnitTestDependencyParser();
    void refreshProjectStructure();
    void fileTreeItemDoubleClicked(QTreeWidgetItem* item, int column);
    void fileTreeHdlFileDoubleClicked(HdlFileTreeWidgetItem* item, int column);
    void closeProjectContentTab(int index);
};

#endif // MAINWINDOW_H
