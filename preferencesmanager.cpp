#include "preferencesmanager.h"

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
