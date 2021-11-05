#ifndef DEPENDENCYPARSERGENERICDEFINITION_H
#define DEPENDENCYPARSERGENERICDEFINITION_H

#include <QString>
#include <QList>

class DependencyParserGenericDefinition
{
public:
    DependencyParserGenericDefinition();
    DependencyParserGenericDefinition(QString name, QString type);

    static QList<DependencyParserGenericDefinition> parseText(QString text);

    bool operator==(const DependencyParserGenericDefinition& other);

    QString name() const;
    void setName(QString name);

    QString type() const;
    void setType(QString type);

private:
    static const QString GENERIC_PATTERN;

    QString mName;
    QString mType;
};

#endif // DEPENDENCYPARSERGENERICDEFINITION_H
