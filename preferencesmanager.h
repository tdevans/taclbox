#ifndef PREFERENCESMANAGER_H
#define PREFERENCESMANAGER_H

#include <QSettings>
#include <QSize>
#include <QPoint>
#include <QByteArray>
#include <QStringList>

class PreferencesManager
{
public:
    PreferencesManager();

    bool mainWindowMaximized() const;
    void setMainWindowMaximized(bool max);
    QSize mainWindowSize() const;
    void setMainWindowSize(QSize size);
    QPoint mainWindowPos() const;
    void setMainWindowPos(QPoint pos);
    QByteArray mainWindowSplitterState() const;
    void setMainWindowSplitterState(QByteArray state);
    QStringList mainWindowRecentProjects() const;
    void setMainWindowMostRecentProject(QString project);

private:
    static const int MAX_RECENT_PROJECTS;

    QSettings mSettings;

};

#endif // PREFERENCESMANAGER_H
