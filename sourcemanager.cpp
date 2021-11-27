#include "sourcemanager.h"

SourceManager::SourceManager(ProjectManager* projectManager)
    : mProjectManager(projectManager), mErrorMessage(QString())
{

}

bool SourceManager::error() const
{
    return !mErrorMessage.isNull();
}

QString SourceManager::errorMessage() const
{
    return mErrorMessage;
}

QFileInfoList SourceManager::sourceFiles()
{
    if (mProjectManager)
    {
        QStringList filters;
        filters << "*.vhd" << "*.v" << "*.sv";

        QDir sourceDir = mProjectManager->projectDir();
        if (sourceDir.cd("source"))
        {
            return sourceDir.entryInfoList(filters);
        }
        else
        {
            mErrorMessage = "Unable to CD to source folder of project.";
            return QFileInfoList();
        }
    }
    else
    {
        return QFileInfoList();
    }
}
