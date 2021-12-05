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
#include <QDir>

MainWindow::MainWindow(PreferencesManager *preferencesManager, ProjectManager* projectManager, SourceManager *sourceManager, QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), mProjectManager(projectManager), mSourceManager(sourceManager), mPreferencesManager(preferencesManager), mProjectSummaryTab(nullptr)
{
    // Initial UI setup
    ui->setupUi(this);
    ui->projectContentTabWidget->clear();
    ui->structureRefreshButton->setDisabled(true);


    // Set up some top level folders in the file browser for now
    mSourceFilesTreeWidgetItem = new QTreeWidgetItem();
    mSourceFilesTreeWidgetItem->setText(0, "Source");

    mTestbenchFilesTreeWidgetItem = new QTreeWidgetItem();
    mTestbenchFilesTreeWidgetItem->setText(0, "Testbench");

    ui->projectFilesTreeWidget->addTopLevelItem(mSourceFilesTreeWidgetItem);
    ui->projectFilesTreeWidget->addTopLevelItem(mTestbenchFilesTreeWidgetItem);


    // Set up a visible handle on the splitter
    // Weird QT workaround
    QSplitterHandle* mainSplitterHandle = ui->splitter->handle(1);
    QVBoxLayout* splitterLayout = new QVBoxLayout(mainSplitterHandle);
    splitterLayout->setSpacing(0);
    splitterLayout->setMargin(0);
    QFrame* splitterLine = new QFrame(mainSplitterHandle);
    splitterLine->setFrameShape(QFrame::VLine);
    splitterLine->setFrameShadow(QFrame::Sunken);
    splitterLayout->addWidget(splitterLine);


    // Set up the window position and size based on our save user preferences
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


    // Add any recently used projects to the recent projects list
    refreshRecentProjects();


    // Setup our menu buttons to do stuff
    connect(ui->action_Open, &QAction::triggered, this, &MainWindow::openProjectDialog);
    connect(ui->actionClose_Project, &QAction::triggered, this, &MainWindow::closeProject);
    connect(ui->actionExit, &QAction::triggered, qApp, &QCoreApplication::exit);
    connect(ui->actionDependency_Parser, &QAction::triggered, this, &MainWindow::openUnitTestDependencyParser);

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

void MainWindow::refreshRecentProjects()
{
    // Regardless of whether we have access to a new list, delete the old one
    for (auto& a : mRecentProjectActions)
    {
        ui->menuFile->removeAction(a);
        delete a;
    }

    mRecentProjectActions.clear();

    if (mPreferencesManager)
    {
        QStringList recentProjects = mPreferencesManager->mainWindowRecentProjects();

        for (auto& p : recentProjects)
        {
            QAction* a = new QAction(p);
            if (a)
            {
                ui->menuFile->insertAction(ui->actionExit, a);
                mRecentProjectActions.append(a);
                connect(a, &QAction::triggered, this, &MainWindow::openRecentProject);
            }
        }

        QAction* s = ui->menuFile->insertSeparator(ui->actionExit);
        mRecentProjectActions.append(s);
    }
    else
    {
        qDebug() << "Somehow, there was no pointer to a preferences manager set in MainWindow";
    }
}

void MainWindow::updateProject()
{
    if (mProjectManager->project())
    {
        ui->actionClose_Project->setEnabled(true);
        ui->structureRefreshButton->setEnabled(true);

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
        if (mProjectSummaryTab)
        {
            delete mProjectSummaryTab;
            mProjectSummaryTab = nullptr;
        }
        ui->actionClose_Project->setEnabled(false);
        ui->structureRefreshButton->setEnabled(false);
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

void MainWindow::openProject(QString prjFile)
{
    if (!prjFile.isEmpty())
    {
        if (mProjectManager)
        {
            prjFile = QDir::cleanPath(prjFile);

            if (mProjectManager->openProject(prjFile))
            {
                mPreferencesManager->setMainWindowMostRecentProject(prjFile);
                refreshRecentProjects();
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

void MainWindow::openRecentProject()
{
    QAction* act = qobject_cast<QAction*>(sender());
    if (act)
    {
        openProject(act->text());
    }
}

void MainWindow::openProjectDialog()
{
    QString prjFile = QFileDialog::getOpenFileName(this, "Open Project", "", "TACL Project (*.tacl)");
    openProject(prjFile);
}

void MainWindow::closeProject()
{
    if (mProjectManager)
    {
        if (mProjectManager->projectIsOpen())
        {
            mProjectManager->closeProject();
            updateProject();
        }
    }
    else
    {
        qDebug() << "The ProjectManager pointer passed to MainWindow was null.";
    }
}

void MainWindow::openUnitTestDependencyParser()
{
    UnitTestHdlParserDialog* u = new UnitTestHdlParserDialog(this);
    u->setAttribute(Qt::WA_DeleteOnClose);
    u->show();
}
