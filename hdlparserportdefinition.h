#ifndef HDLPARSERPORTDEFINITION_H
#define HDLPARSERPORTDEFINITION_H

#include <QString>
#include <QList>

#include "hdlparserportdirection.h"

// Forward declare so we can make the pointer w/o including the
// file, which would cause a circular reference because HdlFile
// contains HdlParserArchitectureDefinitions.
class HdlFile;

class HdlParserPortDefinition
{
public:
    static QList<HdlParserPortDefinition> parseText(const QStringRef text, HdlFile& file, int startingLine);

    QString name() const;
    HdlParserPortDirection dir() const;
    QString type() const;
    HdlFile& file() const;
    int lineNum() const;

private:
    static const QString PORT_PATTERN;

    QString mName;
    HdlParserPortDirection mDir;
    QString mType;
    HdlFile& mFile;
    int mLineNum;

    HdlParserPortDefinition(QString name, HdlParserPortDirection dir, QString type, HdlFile& file, int lineNum);
};

#endif // HDLPARSERPORTDEFINITION_H
