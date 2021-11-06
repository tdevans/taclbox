#ifndef HDLPARSERGENERICDEFINITION_H
#define HDLPARSERGENERICDEFINITION_H

#include <QString>
#include <QList>

class HdlParserGenericDefinition
{
public:
    HdlParserGenericDefinition();
    HdlParserGenericDefinition(QString name, QString type);

    static QList<HdlParserGenericDefinition> parseText(QString text);

    bool operator==(const HdlParserGenericDefinition& other);

    QString name() const;
    void setName(QString name);

    QString type() const;
    void setType(QString type);

private:
    static const QString GENERIC_PATTERN;

    QString mName;
    QString mType;
};

#endif // HDLPARSERGENERICDEFINITION_H
