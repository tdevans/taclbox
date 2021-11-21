#include "project.h"
#include "invalidprojectfileexception.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QVariant>
#include <QDebug>

Project::Project()
{

}

Project Project::load(QString projectFile)
{
    QFile f(projectFile);
    Project prj;

    if (!f.open(QIODevice::ReadOnly))
    {
        throw InvalidProjectFileException(QString("Unable to open specified project file: %1").arg(projectFile));
    }

    prj.mProjectFile = projectFile;

    QJsonDocument jsonDoc = QJsonDocument::fromJson(f.readAll());
    f.close();

    if (jsonDoc.isNull())
    {
        throw InvalidProjectFileException(QString("The specified project file %1 was not a valid JSON file").arg(projectFile));
    }

    if (!jsonDoc.isObject())
    {
        throw InvalidProjectFileException(QString("The specified project file %1 is not a JSON object").arg(projectFile));
    }

    QJsonObject jsonObj = jsonDoc.object();


    SemanticVersion taclVersion = parseTaclVersion(jsonObj);

    if (taclVersion.major() == 1)
    {
        if (taclVersion.minor() == 0)
        {
            if (taclVersion.patch() == 0)
            {
                prj.mVersion = parseProjectVersion(jsonObj);
            }
            else
            {
                throw InvalidProjectFileException(QString("Don't know how to parse a project file from TACL version %1.%2.%3").arg(taclVersion.major()).arg(taclVersion.minor()).arg(taclVersion.patch()));
            }
        }
        else
        {
            throw InvalidProjectFileException(QString("Don't know how to parse a project file from TACL version %1.%2.x").arg(taclVersion.major()).arg(taclVersion.minor()));
        }
    }
    else
    {
        throw InvalidProjectFileException(QString("Don't know how to parse a project file from TACL version %1.x.x").arg(taclVersion.major()));
    }



    return prj;
}

bool Project::save()
{
    return save(mProjectFile);
}

SemanticVersion Project::version() const
{
    return mVersion;
}

void Project::setVersion(SemanticVersion version)
{
    mVersion = version;
}

SemanticVersion Project::parseTaclVersion(QJsonObject prj)
{
    SemanticVersion version;

    if (!prj.contains("taclVersion"))
    {
        throw InvalidProjectFileException("The specified project file does not contain the required key 'taclVersion'");
    }

    if (!prj["taclVersion"].isObject())
    {
        throw InvalidProjectFileException("The key 'taclVersion' in the specified project file is not a JSON object");
    }

    QJsonObject jsonVersion = prj["taclVersion"].toObject();

    if (!jsonVersion.contains("major"))
    {
        throw InvalidProjectFileException("The key 'taclVersion' in the specified project file does not contain the expected subkey 'major'");
    }

    if (!jsonVersion.contains("minor"))
    {
        throw InvalidProjectFileException("The key 'taclVersion' in the specified project file does not contain the expected subkey 'minor'");
    }

    if (!jsonVersion.contains("patch"))
    {
        throw InvalidProjectFileException("The key 'taclVersion' in the specified project file does not contain the expected subkey 'patch'");
    }

    QVariant v = jsonVersion["major"].toVariant();
    bool ok = false;
    int i = v.toInt(&ok);
    if (!ok)
        throw InvalidProjectFileException("The key 'taclVersion.major' is not a valid integer value");
    version.setMajor(i);

    v = jsonVersion["minor"].toVariant();
    ok = false;
    i = v.toInt(&ok);
    if (!ok)
        throw InvalidProjectFileException("The key 'taclVersion.minor' is not a valid integer value");
    version.setMinor(i);

    v = jsonVersion["patch"].toVariant();
    ok = false;
    i = v.toInt(&ok);
    if (!ok)
        throw InvalidProjectFileException("The key 'taclVersion.patch' is not a valid integer value");
    version.setPatch(i);

    return version;
}

SemanticVersion Project::parseProjectVersion(QJsonObject prj)
{
    SemanticVersion version;

    if (!prj.contains("projectVersion"))
    {
        throw InvalidProjectFileException("The specified project file does not contain the required key 'projectVersion'");
    }

    if (!prj["projectVersion"].isObject())
    {
        throw InvalidProjectFileException("The key 'projectVersion' in the specified project file is not a JSON object");
    }

    QJsonObject jsonVersion = prj["projectVersion"].toObject();

    if (!jsonVersion.contains("major"))
    {
        throw InvalidProjectFileException("The key 'projectVersion' in the specified project file does not contain the expected subkey 'major'");
    }

    if (!jsonVersion.contains("minor"))
    {
        throw InvalidProjectFileException("The key 'projectVersion' in the specified project file does not contain the expected subkey 'minor'");
    }

    if (!jsonVersion.contains("patch"))
    {
        throw InvalidProjectFileException("The key 'projectVersion' in the specified project file does not contain the expected subkey 'patch'");
    }

    QVariant v = jsonVersion["major"].toVariant();
    bool ok = false;
    int i = v.toInt(&ok);
    if (!ok)
        throw InvalidProjectFileException("The key 'projectVersion.major' is not a valid integer value");
    version.setMajor(i);

    v = jsonVersion["minor"].toVariant();
    ok = false;
    i = v.toInt(&ok);
    if (!ok)
        throw InvalidProjectFileException("The key 'projectVersion.minor' is not a valid integer value");
    version.setMinor(i);

    v = jsonVersion["patch"].toVariant();
    ok = false;
    i = v.toInt(&ok);
    if (!ok)
        throw InvalidProjectFileException("The key 'projectVersion.patch' is not a valid integer value");
    version.setPatch(i);

    return version;
}
