#include "project.h"

Project::Project()
{

}

QString Project::name() const
{
    return mName;
}

void Project::setName(QString name)
{
    mName = name;
}

SemanticVersion Project::version() const
{
    return mProjectVersion;
}

void Project::setVersion(SemanticVersion version)
{
    mProjectVersion = version;
}

SemanticVersion Project::taclVersion() const
{
    return mTaclVersion;
}

void Project::setTaclVersion(SemanticVersion version)
{
    mTaclVersion = version;
}

QString Project::file() const
{
    return mProjectFile;
}

void Project::setFile(QString filepath)
{
    mProjectFile = filepath;
}
