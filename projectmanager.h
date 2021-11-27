#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QJsonObject>
#include <QDir>

#include "project.h"

class ProjectManager
{
public:
    explicit ProjectManager();

    const Project* project() const;

    bool projectIsOpen() const;
    bool projectIsDirty() const;

    bool error() const;
    QString errorMessage() const;

    bool createProject(QString projectDir, QString projectName);
    bool openProject(QString projectFile);
    void closeProject();
    bool saveProject();

    QDir projectDir() const;

private:
     Project* mProject;
     bool mProjectDirty;
     QString mErrorMessage;

     SemanticVersion parseTaclVersion(QJsonObject rootObj);
     QString parseProjectName(QJsonObject rootObj);
     SemanticVersion parseProjectVersion(QJsonObject rootObj);
};

#endif // PROJECTMANAGER_H
