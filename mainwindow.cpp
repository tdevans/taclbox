#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "unittesthdlparserdialog.h"
#include <QFileDialog>
#include "projectsummarywidget.h"

MainWindow::MainWindow(ProjectManager* prjManager, QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), mProjectManager(prjManager), mProjectSummaryTab(nullptr)
{
    ui->setupUi(this);
    ui->projectTabWidget->clear();

    QSplitterHandle* mainSplitterHandle = ui->splitter->handle(1);
    QVBoxLayout* splitterLayout = new QVBoxLayout(mainSplitterHandle);
    splitterLayout->setSpacing(0);
    splitterLayout->setMargin(0);
    QFrame* splitterLine = new QFrame(mainSplitterHandle);
    splitterLine->setFrameShape(QFrame::VLine);
    splitterLine->setFrameShadow(QFrame::Sunken);
    splitterLayout->addWidget(splitterLine);

    connect(ui->action_Open, &QAction::triggered, this, &MainWindow::openProject);
    connect(ui->actionExit, &QAction::triggered, qApp, &QCoreApplication::exit);
    connect(ui->actionDependency_Parser, &QAction::triggered, this, &MainWindow::openUnitTestDependencyParser);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateProject()
{
    if (mProjectManager->project())
    {
        if (!mProjectSummaryTab)
        {
            mProjectSummaryTab = new ProjectSummaryWidget;

            if (mProjectSummaryTab)
            {
                ui->projectTabWidget->addTab(mProjectSummaryTab, "Project Summary");
            }
            else
            {
                qDebug() << "Failed to allocate new ProjectSummaryWidget";
            }
        }

        if (mProjectSummaryTab)
        {
            mProjectSummaryTab->setProjectName(mProjectManager->project()->name());
            mProjectSummaryTab->setProjectVersion(mProjectManager->project()->version());
        }

    }
    else
    {
        qDebug() << "No project is open";
        ui->projectTabWidget->clear();
    }
}

void MainWindow::openProject()
{
    QString prjFile = QFileDialog::getOpenFileName(this, "Open Project", "", "TACL Project (*.tacl)");
    if (!prjFile.isEmpty())
    {
        if (mProjectManager)
        {
            if (mProjectManager->openProject(prjFile))
            {
                updateProject();
            }
            else
            {
                qDebug() << "Unable to open the specified project";
                if (mProjectManager->error())
                {
                    qDebug() << mProjectManager->errorMessage();
                }
            }
        }
        else
        {
            qDebug() << "The ProjectManager pointer passed to MainWindow was null.";
        }
    }
}

void MainWindow::openUnitTestDependencyParser()
{
    UnitTestHdlParserDialog* u = new UnitTestHdlParserDialog(this);
    u->setAttribute(Qt::WA_DeleteOnClose);
    u->show();
}
