#include "dependencyparserarchitecturedefinition.h"

const QString DependencyParserArchitectureDefinition::ARCHITECTURE_START_PATTERN = "architecture\\s+(?<name>[a-zA-Z][a-zA-Z0-9_]*)\\s+of\\s+(?<entity>[a-zA-Z][a-zA-Z0-9_]*)\\s+is";
const QString DependencyParserArchitectureDefinition::ARCHITECTURE_END_PATTERN = "end\\s+(?:architecture\\s+)?%1;"; // Need to fill in the architecture name before matching

DependencyParserArchitectureDefinition::DependencyParserArchitectureDefinition()
{

}

DependencyParserArchitectureDefinition::DependencyParserArchitectureDefinition(QString name, QString entityName)
    : mName(name), mEntityName(entityName)
{

}

QList<DependencyParserArchitectureDefinition> DependencyParserArchitectureDefinition::parseText(QString text)
{
    QList<DependencyParserArchitectureDefinition> architectures;

    return architectures;
}

QString DependencyParserArchitectureDefinition::name() const
{
    return mName;
}

void DependencyParserArchitectureDefinition::setName(QString name)
{
    mName = name;
}

QString DependencyParserArchitectureDefinition::entityName() const
{
    return mEntityName;
}

void DependencyParserArchitectureDefinition::setEntityName(QString entityName)
{
    mEntityName = entityName;
}
