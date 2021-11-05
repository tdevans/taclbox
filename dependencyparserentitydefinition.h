#ifndef DEPENDENCYPARSERENTITYDEFINITION_H
#define DEPENDENCYPARSERENTITYDEFINITION_H

#include <QList>

#include "dependencyparsergenericdefinition.h"
#include "dependencyparserportdefinition.h"

class DependencyParserEntityDefinition
{
public:
    DependencyParserEntityDefinition();
    DependencyParserEntityDefinition(QString name);

    static QList<DependencyParserEntityDefinition> parseText(QString text);

    QString name() const;
    void setName(QString n);

    QList<DependencyParserGenericDefinition> generics() const;
    void setGenerics(QList<DependencyParserGenericDefinition> genericList);
    void addGeneric(DependencyParserGenericDefinition generic);
    void addGeneric(QString name, QString type);
    void removeGeneric(DependencyParserGenericDefinition generic);
    void removeGeneric(QString name);

    QList<DependencyParserPortDefinition> ports() const;
    void setPorts(QList<DependencyParserPortDefinition> portList);
    void addPort(DependencyParserPortDefinition port);
    void addPort(QString name, ePortDir dir, QString type);
    void removePort(DependencyParserPortDefinition port);
    void removePort(QString name);

private:
    static const QString ENTITY_START_PATTERN;
    static const QString ENTITY_END_PATTERN;
    static const QString GENERIC_SECTION_START_PATTERN;
    static const QString PORT_SECTION_START_PATTERN;
    static const QString GENERIC_OR_PORT_SECTION_END_PATTERN;

    QString mName;
    QList<DependencyParserGenericDefinition> mGenerics;
    QList<DependencyParserPortDefinition> mPorts;

};

#endif // DEPENDENCYPARSERENTITYDEFINITION_H
