#ifndef HDLPARSERARCHITECTUREDEFINITION_H
#define HDLPARSERARCHITECTUREDEFINITION_H

#include <QString>
#include <QList>

class HdlParserArchitectureDefinition
{
public:
    HdlParserArchitectureDefinition();
    HdlParserArchitectureDefinition(QString name, QString entityName);

    static QList<HdlParserArchitectureDefinition> parseText(QString text);

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

#endif // HDLPARSERARCHITECTUREDEFINITION_H
