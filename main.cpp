#include "mainwindow.h"
#include "preferencesmanager.h"
#include "projectmanager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    PreferencesManager prefMgr;
    ProjectManager prjMgr;

    MainWindow w(prefMgr, prjMgr);
    w.show();

    return a.exec();
}
