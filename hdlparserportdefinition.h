#ifndef HDLPARSERPORTDEFINITION_H
#define HDLPARSERPORTDEFINITION_H

#include <QString>
#include <QList>

enum ePortDir {IN, OUT, BIDIR};

class HdlParserPortDefinition
{
public:
    HdlParserPortDefinition();
    HdlParserPortDefinition(QString name, ePortDir dir, QString type);

    static QList<HdlParserPortDefinition> parseText(QString text);

    bool operator==(const HdlParserPortDefinition& other);

    QString name() const;
    void setName(QString name);

    ePortDir dir() const;
    QString dirString() const;
    void setDir(ePortDir dir);

    QString type() const;
    void setType(QString type);

private:
    static const QString PORT_PATTERN;

    QString mName;
    ePortDir mDir;
    QString mType;

};

#endif // HDLPARSERPORTDEFINITION_H
