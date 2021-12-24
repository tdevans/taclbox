#ifndef HDLPARSERARCHITECTUREDEFINITION_H
#define HDLPARSERARCHITECTUREDEFINITION_H

#include <QString>
#include <QList>
#include "hdlparsertypedefinition.h"
#include "hdlparsersignaldefinition.h"

// Forward declare so we can make the pointer w/o including the
// file, which would cause a circular reference because HdlFile
// contains HdlParserArchitectureDefinitions.
class HdlFile;

class HdlParserArchitectureDefinition
{
public:
    static QList<HdlParserArchitectureDefinition> parseText(const QStringRef text, HdlFile& file, int startingLine);

    QString name() const;
    QString entityName() const;
    HdlFile& file() const;
    int lineNum() const;

    QList<HdlParserTypeDefinition> types() const;
    QList<HdlParserSignalDefinition> sigs() const;


private:
    static const QString ARCHITECTURE_START_PATTERN;
    static const QString ARCHITECTURE_END_PATTERN;

    QString mName;
    QString mEntityName;
    HdlFile& mFile;
    int mLineNum;

    QList<HdlParserTypeDefinition> mTypes;
    QList<HdlParserSignalDefinition> mSigs;

    HdlParserArchitectureDefinition(QString name, QString entityName, HdlFile& file, int lineNum);

};

#endif // HDLPARSERARCHITECTUREDEFINITION_H
