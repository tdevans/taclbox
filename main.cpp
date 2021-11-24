#include "mainwindow.h"
#include "projectmanager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ProjectManager pm;

    MainWindow w(&pm);
    w.show();

    return a.exec();
}
