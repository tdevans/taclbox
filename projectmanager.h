#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QJsonObject>
#include <QDir>
#include <QFileSystemWatcher>
#include "project.h"

class ProjectManager
{
public:
    explicit ProjectManager();

    Project* project() const;

    bool projectIsOpen() const;
    bool projectIsDirty() const;

    bool error() const;
    QString errorMessage() const;

    bool createProject(QString projectDir, QString projectName);
    bool openProject(QString projectFile);
    void closeProject();
    bool saveProject();

    QString projectPath() const;
    QString sourcePath() const;
    QString testbenchPath() const;

private:
     Project* mProject;
     bool mProjectDirty;
     QString mErrorMessage;

     SemanticVersion parseTaclVersion(QJsonObject rootObj);
     QString parseProjectName(QJsonObject rootObj);
     SemanticVersion parseProjectVersion(QJsonObject rootObj);
};

#endif // PROJECTMANAGER_H
