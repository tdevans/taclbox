#ifndef DEPENDENCYPARSERPORTDEFINITION_H
#define DEPENDENCYPARSERPORTDEFINITION_H

#include <QString>
#include <QList>

enum ePortDir {IN, OUT};

class DependencyParserPortDefinition
{
public:
    DependencyParserPortDefinition();
    DependencyParserPortDefinition(QString name, ePortDir dir, QString type);

    static QList<DependencyParserPortDefinition> parseText(QString text);

    bool operator==(const DependencyParserPortDefinition& other);

    QString name() const;
    void setName(QString name);

    ePortDir dir() const;
    void setDir(ePortDir dir);

    QString type() const;
    void setType(QString type);

private:
    QString mName;
    ePortDir mDir;
    QString mType;

};

#endif // DEPENDENCYPARSERPORTDEFINITION_H
