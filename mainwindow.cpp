#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "unittesthdlparserdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionDependency_Parser, &QAction::triggered, this, &MainWindow::openUnitTestDependencyParser);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openUnitTestDependencyParser()
{
    UnitTestHdlParserDialog* u = new UnitTestHdlParserDialog(this);
    u->setAttribute(Qt::WA_DeleteOnClose);
    u->show();
}
