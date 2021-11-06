#ifndef DEPENDENCYPARSERARCHITECTUREDEFINITION_H
#define DEPENDENCYPARSERARCHITECTUREDEFINITION_H

#include <QString>
#include <QList>

class DependencyParserArchitectureDefinition
{
public:
    DependencyParserArchitectureDefinition();
    DependencyParserArchitectureDefinition(QString name, QString entityName);

    static QList<DependencyParserArchitectureDefinition> parseText(QString text);

    QString name() const;
    void setName(QString name);

    QString entityName() const;
    void setEntityName(QString entityName);

private:
    static const QString ARCHITECTURE_START_PATTERN;
    static const QString ARCHITECTURE_END_PATTERN;

    QString mName;
    QString mEntityName;

};

#endif // DEPENDENCYPARSERARCHITECTUREDEFINITION_H
