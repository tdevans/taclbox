#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "projectmanager.h"
#include "projectsummarywidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(ProjectManager* prjManager, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ProjectManager* mProjectManager;

    ProjectSummaryWidget* mProjectSummaryTab;

    void updateProject();

private slots:
    void openProject();
    void openUnitTestDependencyParser();
};

#endif // MAINWINDOW_H
