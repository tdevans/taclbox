#include "mainwindow.h"
#include "preferencesmanager.h"
#include "projectmanager.h"
#include "sourcemanager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    PreferencesManager prefMgr;
    ProjectManager prjMgr;
    SourceManager srcMgr(&prjMgr);

    MainWindow w(&prefMgr, &prjMgr, &srcMgr);
    w.show();

    return a.exec();
}
