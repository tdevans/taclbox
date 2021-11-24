#include "projectmanager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>

ProjectManager::ProjectManager() :
    mProject(nullptr), mProjectDirty(false), mErrorMessage(QString())
{

}

const Project* ProjectManager::project() const
{
    return mProject;
}

bool ProjectManager::projectIsOpen() const
{
    return (bool)mProject;
}

bool ProjectManager::projectIsDirty() const
{
    return mProjectDirty;
}

bool ProjectManager::error() const
{
    return !mErrorMessage.isNull();
}

QString ProjectManager::errorMessage() const
{
    return mErrorMessage;
}

bool ProjectManager::createProject(QString projectDir, QString projectName)
{
    mErrorMessage = "The create project function is not yet implemented.";
    return false;
}

bool ProjectManager::openProject(QString projectFile)
{
    if (projectIsOpen())
    {
        closeProject();
    }

    QFile f(projectFile);
    Project* prj = new Project();

    if (f.open(QIODevice::ReadOnly))
    {
        prj->setFile(projectFile);

        QJsonDocument jsonDoc = QJsonDocument::fromJson(f.readAll());
        f.close();

        if (!jsonDoc.isNull())
        {
            if (jsonDoc.isObject())
            {
                QJsonObject jsonObj = jsonDoc.object();

                prj->setTaclVersion(parseTaclVersion(jsonObj));

                if (!error())
                {
                    if (prj->taclVersion().major() == 1)
                    {
                        if (prj->taclVersion().minor() == 0)
                        {
                            if (prj->taclVersion().patch() == 0)
                            {
                                prj->setName(parseProjectName(jsonObj));

                                if (!error())
                                {
                                    prj->setVersion(parseProjectVersion(jsonObj));
                                }
                            }
                            else
                            {
                                mErrorMessage = QString("Don't know how to parse a project file from TACL version %1.%2.%3").arg(prj->taclVersion().major()).arg(prj->taclVersion().minor()).arg(prj->taclVersion().patch());
                            }
                        }
                        else
                        {
                            mErrorMessage = QString("Don't know how to parse a project file from TACL version %1.%2.x").arg(prj->taclVersion().major()).arg(prj->taclVersion().minor());
                        }
                    }
                    else
                    {
                        mErrorMessage = QString("Don't know how to parse a project file from TACL version %1.x.x").arg(prj->taclVersion().major());
                    }
                }
            }
            else
            {
                mErrorMessage = QString("The specified project file %1 is not a JSON object").arg(projectFile);
            }
        }
        else
        {
            mErrorMessage = QString("The specified project file %1 was not a valid JSON file").arg(projectFile);
        }
    }
    else
    {
        mErrorMessage = QString("Unable to open specified project file: %1").arg(projectFile);
    }

    if (error())
    {
        delete prj;
    }
    else
    {
        mProject = prj;
    }

    return !error();
}

void ProjectManager::closeProject()
{
    if (mProject)
    {
        delete mProject;
        mProject = nullptr;
    }
    mProjectDirty = false;
}

bool ProjectManager::saveProject()
{
    if (mProject)
    {
        QFile f(mProject->file());
        if (!f.open(QIODevice::WriteOnly))
        {
            mErrorMessage = QString("Unable to open the specified project file: %1").arg(mProject->file());
            return false;
        }

        QJsonObject taclVersion;
        taclVersion["major"] = 1;
        taclVersion["minor"] = 0;
        taclVersion["patch"] = 0;

        QJsonObject projectVersion;
        projectVersion["major"] = mProject->version().major();
        projectVersion["minor"] = mProject->version().minor();
        projectVersion["patch"] = mProject->version().patch();

        QJsonObject rootObj;
        rootObj["taclVersion"] = taclVersion;
        rootObj["projectVersion"] = projectVersion;
        rootObj["projectName"] = mProject->name();

        QJsonDocument prjDoc;
        prjDoc.setObject(rootObj);

        f.write(prjDoc.toJson(QJsonDocument::Indented));
        f.close();
        mProjectDirty = false;
        return true;
    }
    else
    {
        mErrorMessage = "There is no project open to save";
        return false;
    }
}

SemanticVersion ProjectManager::parseTaclVersion(QJsonObject rootObj)
{
    SemanticVersion version;

    if (rootObj.contains("taclVersion"))
    {
        if (rootObj["taclVersion"].isObject())
        {
            QJsonObject jsonVersion = rootObj["taclVersion"].toObject();

            if (jsonVersion.contains("major"))
            {
                if (jsonVersion.contains("minor"))
                {
                    if (jsonVersion.contains("patch"))
                    {
                        QVariant v = jsonVersion["major"].toVariant();
                        bool ok = false;
                        int i = v.toInt(&ok);
                        if (ok)
                        {
                            version.setMajor(i);

                            v = jsonVersion["minor"].toVariant();
                            ok = false;
                            i = v.toInt(&ok);
                            if (ok)
                            {
                                version.setMinor(i);

                                v = jsonVersion["patch"].toVariant();
                                ok = false;
                                i = v.toInt(&ok);
                                if (ok)
                                {
                                    version.setPatch(i);
                                }
                                else
                                {
                                    mErrorMessage = "The key 'taclVersion.patch' is not a valid integer value";
                                }
                            }
                            else
                            {
                                mErrorMessage = "The key 'taclVersion.minor' is not a valid integer value";
                            }

                        }
                        else
                        {
                            mErrorMessage = "The key 'taclVersion.major' is not a valid integer value";
                        }
                    }
                    else
                    {
                        mErrorMessage = "The key 'taclVersion' in the specified project file does not contain the expected subkey 'patch'";
                    }
                }
                else
                {
                    mErrorMessage = "The key 'taclVersion' in the specified project file does not contain the expected subkey 'minor'";
                }
            }
            else
            {
                mErrorMessage = "The key 'taclVersion' in the specified project file does not contain the expected subkey 'major'";
            }
        }
        else
        {
            mErrorMessage = "The key 'taclVersion' in the specified project file is not a JSON object";
        }
    }
    else
    {
        mErrorMessage = "The specified project file does not contain the required key 'taclVersion'";
    }

    return version;
}

QString ProjectManager::parseProjectName(QJsonObject rootObj)
{
    QString name;

    if (rootObj.contains("projectName"))
    {
        if (rootObj["projectName"].isString())
        {
            name = rootObj["projectName"].toString();
        }
        else
        {
            mErrorMessage = "The key 'projectName' is not a valid string.";
        }
    }
    else
    {
        mErrorMessage = "The specified project file does not contain the required key 'projectName'";
    }

    return name;
}

SemanticVersion ProjectManager::parseProjectVersion(QJsonObject rootObj)
{
    SemanticVersion version;

    if (rootObj.contains("projectVersion"))
    {
        if (rootObj["projectVersion"].isObject())
        {
            QJsonObject jsonVersion = rootObj["projectVersion"].toObject();

            if (jsonVersion.contains("major"))
            {
                if (jsonVersion.contains("minor"))
                {
                    if (jsonVersion.contains("patch"))
                    {
                        QVariant v = jsonVersion["major"].toVariant();
                        bool ok = false;
                        int i = v.toInt(&ok);
                        if (ok)
                        {
                            version.setMajor(i);

                            v = jsonVersion["minor"].toVariant();
                            ok = false;
                            i = v.toInt(&ok);
                            if (ok)
                            {
                                version.setMinor(i);

                                v = jsonVersion["patch"].toVariant();
                                ok = false;
                                i = v.toInt(&ok);
                                if (ok)
                                {
                                    version.setPatch(i);
                                }
                                else
                                {
                                    mErrorMessage = "The key 'projectVersion.patch' is not a valid integer value";
                                }
                            }
                            else
                            {
                                mErrorMessage = "The key 'projectVersion.minor' is not a valid integer value";
                            }

                        }
                        else
                        {
                            mErrorMessage = "The key 'projectVersion.major' is not a valid integer value";
                        }
                    }
                    else
                    {
                        mErrorMessage = "The key 'projectVersion' in the specified project file does not contain the expected subkey 'patch'";
                    }
                }
                else
                {
                    mErrorMessage = "The key 'projectVersion' in the specified project file does not contain the expected subkey 'minor'";
                }
            }
            else
            {
                mErrorMessage = "The key 'projectVersion' in the specified project file does not contain the expected subkey 'major'";
            }
        }
        else
        {
            mErrorMessage = "The key 'projectVersion' in the specified project file is not a JSON object";
        }
    }
    else
    {
        mErrorMessage = "The specified project file does not contain the required key 'projectVersion'";
    }

    return version;
}
