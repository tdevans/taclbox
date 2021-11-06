#ifndef HDLPARSERSIGNALDEFINITION_H
#define HDLPARSERSIGNALDEFINITION_H

#include <QString>
#include <QList>

class HdlParserSignalDefinition
{
public:
    HdlParserSignalDefinition();
    HdlParserSignalDefinition(QString name, QString typeName);

    QList<HdlParserSignalDefinition> parseText(QString text);

    bool operator==(const HdlParserSignalDefinition& other);

    QString name() const;
    void setName(QString name);

    QString typeName() const;
    void setTypeName(QString typeName);

private:
    static const QString SIGNAL_PATTERN;

    QString mName;
    QString mTypeName;
};

#endif // HDLPARSERSIGNALDEFINITION_H
