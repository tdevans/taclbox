#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "unittesthdlparserdialog.h"
#include <QFileDialog>
#include <QFileInfoList>
#include <QTreeWidgetItem>
#include "projectsummarywidget.h"
#include <QGuiApplication>
#include <QScreen>
#include <QMessageBox>
#include <QCloseEvent>

MainWindow::MainWindow(PreferencesManager *preferencesManager, ProjectManager* projectManager, SourceManager *sourceManager, QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), mPreferencesManager(preferencesManager), mProjectManager(projectManager), mSourceManager(sourceManager), mProjectSummaryTab(nullptr)
{
    ui->setupUi(this);
    ui->projectContentTabWidget->clear();

    mSourceFilesTreeWidgetItem = new QTreeWidgetItem();
    mSourceFilesTreeWidgetItem->setText(0, "Source");

    mTestbenchFilesTreeWidgetItem = new QTreeWidgetItem();
    mTestbenchFilesTreeWidgetItem->setText(0, "Testbench");

    ui->projectFilesTreeWidget->addTopLevelItem(mSourceFilesTreeWidgetItem);
    ui->projectFilesTreeWidget->addTopLevelItem(mTestbenchFilesTreeWidgetItem);

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

    QPoint p = mPreferencesManager->mainWindowPos();
    QSize s = mPreferencesManager->mainWindowSize();

    if ((p.x() >= qApp->primaryScreen()->availableGeometry().width()) ||  (p.y() >= qApp->primaryScreen()->availableGeometry().height()))
    {
        move(100, 100);
    }
    else
    {
        move(p);
    }

    resize(s);

    if (mPreferencesManager->mainWindowMaximized())
    {
        showMaximized();
    }

    ui->splitter->restoreState(mPreferencesManager->mainWindowSplitterState());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (checkQuit())
    {
        if (isMaximized())
        {
            mPreferencesManager->setMainWindowMaximized(true);
        }
        else
        {
            mPreferencesManager->setMainWindowMaximized(false);
            mPreferencesManager->setMainWindowSize(size());
            mPreferencesManager->setMainWindowPos(pos());
        }

        mPreferencesManager->setMainWindowSplitterState(ui->splitter->saveState());

        event->accept();
    }
    else
    {
        event->ignore();
    }
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
                ui->projectContentTabWidget->addTab(mProjectSummaryTab, "Project Summary");
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

        if (mSourceManager)
        {
            QFileInfoList sfi = mSourceManager->sourceFiles();
            for (auto& fi : sfi)
            {
                QTreeWidgetItem* i = new QTreeWidgetItem();
                if (i)
                {
                    i->setText(0, fi.fileName());
                    mSourceFilesTreeWidgetItem->addChild(i);
                }
                else
                {
                    qDebug() << QString("Failed to allocate new QTreeWidgetItem to display source file %1").arg(fi.fileName());
                }
            }
        }
        else
        {
            qDebug() << "The SourceManager pointer is null in MainWindow";
        }
    }
    else
    {
        qDebug() << "No project is open";
        ui->projectContentTabWidget->clear();
    }
}

bool MainWindow::checkQuit()
{
    if (mProjectManager->projectIsDirty())
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Quit", "Are you sure you want to quit?", QMessageBox::Yes | QMessageBox::No);
        return reply == QMessageBox::Yes;
    }
    else
    {
        return true;
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
