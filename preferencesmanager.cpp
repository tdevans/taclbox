#include "preferencesmanager.h"

const int PreferencesManager::MAX_RECENT_PROJECTS = 5;

PreferencesManager::PreferencesManager()
    : mSettings(QSettings::IniFormat, QSettings::UserScope, "TACL", "Taclbox")
{

}

bool PreferencesManager::mainWindowMaximized() const
{
    return mSettings.value("mainwindow/maximized", false).toBool();
}

void PreferencesManager::setMainWindowMaximized(bool max)
{
    mSettings.setValue("mainwindow/maximized", max);
}

QSize PreferencesManager::mainWindowSize() const
{
    return mSettings.value("mainwindow/size", QSize(1024, 768)).toSize();
}

void PreferencesManager::setMainWindowSize(QSize size)
{
    mSettings.setValue("mainwindow/size", size);
}

QPoint PreferencesManager::mainWindowPos() const
{
    return mSettings.value("mainwindow/pos", QPoint(100, 100)).toPoint();
}

void PreferencesManager::setMainWindowPos(QPoint pos)
{
    mSettings.setValue("mainwindow/pos", pos);
}

QByteArray PreferencesManager::mainWindowSplitterState() const
{
    return mSettings.value("mainwindow/split").toByteArray();
}

void PreferencesManager::setMainWindowSplitterState(QByteArray state)
{
    mSettings.setValue("mainwindow/split", state);
}

QStringList PreferencesManager::mainWindowRecentProjects() const
{
    return mSettings.value("mainwindow/recentprojects").toStringList();
}

void PreferencesManager::setMainWindowMostRecentProject(QString project)
{
    QStringList oldRecentProjects = mainWindowRecentProjects();
    QStringList newRecentProjects;

    newRecentProjects.append(project);
    for (auto& p : oldRecentProjects)
    {
        if (p != project)
        {
            newRecentProjects.append(p);
        }

        if (newRecentProjects.length() >= MAX_RECENT_PROJECTS)
        {
            break;
        }
    }

    mSettings.setValue("mainwindow/recentprojects", newRecentProjects);
}
