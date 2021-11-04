#include "dependencyparsergenericdefinition.h"

DependencyParserGenericDefinition::DependencyParserGenericDefinition()
{

}

DependencyParserGenericDefinition::DependencyParserGenericDefinition(QString name, QString type)
    :mName(name), mType(type)
{

}

QList<DependencyParserGenericDefinition> DependencyParserGenericDefinition::parseText(QString text)
{
    QList<DependencyParserGenericDefinition> g;

    return g;
}

bool DependencyParserGenericDefinition::operator==(const DependencyParserGenericDefinition &other)
{
    if ((other.mName == mName) && (other.mType == mType))
        return true;
    else
        return false;
}

QString DependencyParserGenericDefinition::name() const
{
    return mName;
}

void DependencyParserGenericDefinition::setName(QString name)
{
    mName = name;
}

QString DependencyParserGenericDefinition::type() const
{
    return mType;
}

void DependencyParserGenericDefinition::setType(QString type)
{
    mType = type;
}
