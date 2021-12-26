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
#include <QIcon>
#include "hdlfiletreewidgetitem.h"
#include "texteditorwidget.h"

MainWindow::MainWindow(PreferencesManager &preferencesManager, ProjectManager &projectManager, QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), mProjectManager(projectManager), mPreferencesManager(preferencesManager), mProjectSummaryTab(nullptr)
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
    QPoint p = mPreferencesManager.mainWindowPos();
    QSize s = mPreferencesManager.mainWindowSize();

    if ((p.x() >= qApp->primaryScreen()->availableGeometry().width()) ||  (p.y() >= qApp->primaryScreen()->availableGeometry().height()))
    {
        move(100, 100);
    }
    else
    {
        move(p);
    }

    resize(s);

    if (mPreferencesManager.mainWindowMaximized())
    {
        showMaximized();
    }

    ui->splitter->restoreState(mPreferencesManager.mainWindowSplitterState());


    // Add any recently used projects to the recent projects list
    refreshRecentProjects();


    // Setup our menu buttons to do stuff
    connect(ui->action_Open, &QAction::triggered, this, &MainWindow::openProjectDialog);
    connect(ui->actionClose_Project, &QAction::triggered, this, &MainWindow::closeProject);
    connect(ui->actionExit, &QAction::triggered, qApp, &QCoreApplication::exit);
    connect(ui->actionDependency_Parser, &QAction::triggered, this, &MainWindow::openUnitTestDependencyParser);
    connect(ui->structureRefreshButton, &QPushButton::clicked, this, &MainWindow::refreshProjectStructure);
    connect(ui->projectFilesTreeWidget, &QTreeWidget::itemDoubleClicked, this, &MainWindow::fileTreeItemDoubleClicked);
    connect(ui->projectContentTabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::closeProjectContentTab);
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
            mPreferencesManager.setMainWindowMaximized(true);
        }
        else
        {
            mPreferencesManager.setMainWindowMaximized(false);
            mPreferencesManager.setMainWindowSize(size());
            mPreferencesManager.setMainWindowPos(pos());
        }

        mPreferencesManager.setMainWindowSplitterState(ui->splitter->saveState());

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

    QStringList recentProjects = mPreferencesManager.mainWindowRecentProjects();

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

void MainWindow::updateProject()
{
    if (mProjectManager.project())
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
            mProjectSummaryTab->setProjectName(mProjectManager.project()->name());
            mProjectSummaryTab->setProjectVersion(mProjectManager.project()->version());
        }

        auto& sfi = mProjectManager.project()->sourceFiles();
        for (auto& i : sfi)
        {
            HdlFileTreeWidgetItem* item = new HdlFileTreeWidgetItem(i);
            if (item)
            {
                mSourceFilesTreeWidgetItem->addChild(item);
            }
            else
            {
                qDebug() << QString("Failed to allocate new HdlFileTreeWidgetItem to display source file %1").arg(i.fileName());
            }
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
    if (mProjectManager.projectIsDirty())
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

void MainWindow::addLibraryToStructure(QList<HdlParserLibrary>& lib)
{
    if (!lib.isEmpty())
    {
        QTreeWidgetItem* libItem = new QTreeWidgetItem;
        if (!libItem)
        {
            qDebug() << "Failed to allocate QTreeWidgetItem for library display in project structure";
        }
        else
        {
            libItem->setText(0, lib[0].name());

            // Only do further processing on the library if we successfully parsed only
            // one library with this naem. Otherwise, we want to show the user an error
            // indicator that there is a conflict of library names.
            if (lib.count() == 1)
            {
                for (auto& x : lib[0].packages())
                {
                    addPackageToStructure(libItem, x);
                }
            }

            ui->projectStructureTreeWidget->addTopLevelItem(libItem);
        }
    }
}

void MainWindow::addPackageToStructure(QTreeWidgetItem *lib, QList<HdlParserPackageHeaderDefinition> &pkg)
{
    if (!pkg.isEmpty())
    {
        QTreeWidgetItem* pkgItem = new QTreeWidgetItem;
        if (pkgItem)
        {
            pkgItem->setText(0, pkg[0].name());
            pkgItem->setIcon(0, QIcon(":/icons/icons/package.png"));
            lib->addChild(pkgItem);
        }
        else
        {
            qDebug() << "Unable to allocate QTreeWidgetItem for package in structure";
        }
    }
}

void MainWindow::openProject(QString prjFile)
{
    if (!prjFile.isEmpty())
    {
        prjFile = QDir::cleanPath(prjFile);

        if (mProjectManager.openProject(prjFile))
        {
            mPreferencesManager.setMainWindowMostRecentProject(prjFile);
            refreshRecentProjects();
            updateProject();
        }
        else
        {
            qDebug() << "Unable to open the specified project";
            if (mProjectManager.error())
            {
                qDebug() << mProjectManager.errorMessage();
            }
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
    if (mProjectManager.projectIsOpen())
    {
        mProjectManager.closeProject();
        updateProject();
    }
}

void MainWindow::openUnitTestDependencyParser()
{
    UnitTestHdlParserDialog* u = new UnitTestHdlParserDialog(this);
    u->setAttribute(Qt::WA_DeleteOnClose);
    u->show();
}

void MainWindow::refreshProjectStructure()
{
    ui->projectStructureTreeWidget->clear();
}

void MainWindow::fileTreeItemDoubleClicked(QTreeWidgetItem* item, int column)
{
    HdlFileTreeWidgetItem* hdlFileItem = dynamic_cast<HdlFileTreeWidgetItem*>(item);
    if (hdlFileItem)
    {
        fileTreeHdlFileDoubleClicked(hdlFileItem, column);
    }
}

void MainWindow::fileTreeHdlFileDoubleClicked(HdlFileTreeWidgetItem* item, int column)
{
    auto& fi = item->hdlFile().fileInfo();
    qDebug() << QString("Source file %1 double clicked...").arg(fi.filePath());

    TextEditorWidget* e = nullptr;
    for (int i = 0; i < ui->projectContentTabWidget->count(); ++i)
    {
        e = dynamic_cast<TextEditorWidget*>(ui->projectContentTabWidget->widget(i));
        if (e)
        {
            if (e->fileInfo() == fi)
            {
                qDebug() << QString("Found existing tab for file %1").arg(e->fileInfo().filePath());
                ui->projectContentTabWidget->setCurrentIndex(i);
                break;
            }
            else
            {
                // Reset this for the logic below to know we didn't find a match
                e = nullptr;
            }
        }
    }

    if (!e)
    {
        e = new TextEditorWidget(item->hdlFile().fileInfo());
        if (e)
        {
            int i = ui->projectContentTabWidget->addTab(e, item->hdlFile().fileName());
            ui->projectContentTabWidget->setCurrentIndex(i);
        }
        else
        {
            qDebug() << QString("Unable to allocate TextEditorWidget for file %1").arg(fi.fileName());
        }
    }
}

void MainWindow::closeProjectContentTab(int index)
{
    ui->projectContentTabWidget->removeTab(index);
}
