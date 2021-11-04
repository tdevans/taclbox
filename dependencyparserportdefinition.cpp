#include "dependencyparserportdefinition.h"

DependencyParserPortDefinition::DependencyParserPortDefinition()
{

}

DependencyParserPortDefinition::DependencyParserPortDefinition(QString name, ePortDir dir, QString type)
    :mName(name), mDir(dir), mType(type)
{

}

QList<DependencyParserPortDefinition> DependencyParserPortDefinition::parseText(QString text)
{
    QList<DependencyParserPortDefinition> p;
    return p;
}

bool DependencyParserPortDefinition::operator==(const DependencyParserPortDefinition &other)
{
    if ((other.mType == mType) && (other.mDir == mDir) && (other.mType == mType))
        return true;
    else
        return false;
}

QString DependencyParserPortDefinition::name() const
{
    return mName;
}

void DependencyParserPortDefinition::setName(QString name)
{
    mName = name;
}

ePortDir DependencyParserPortDefinition::dir() const
{
    return mDir;
}

void DependencyParserPortDefinition::setDir(ePortDir dir)
{
    mDir = dir;
}

QString DependencyParserPortDefinition::type() const
{
    return mType;
}

void DependencyParserPortDefinition::setType(QString type)
{
    mType = type;
}
