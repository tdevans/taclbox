#ifndef SOURCEMANAGER_H
#define SOURCEMANAGER_H

#include "projectmanager.h"
#include <QFileInfoList>
#include <QString>

class SourceManager
{
public:
    SourceManager(ProjectManager* projectManager);

    bool error() const;
    QString errorMessage() const;

    QFileInfoList sourceFiles();

private:
    ProjectManager* mProjectManager;
    QString mErrorMessage;
};

#endif // SOURCEMANAGER_H
