#ifndef HDLPARSERENTITYDEFINITION_H
#define HDLPARSERENTITYDEFINITION_H

#include <QList>

#include "hdlparsergenericdefinition.h"
#include "hdlparserportdefinition.h"
#include "hdlparserarchitecturedefinition.h"

// Forward declare so we can make the pointer w/o including the
// file, which would cause a circular reference because HdlFile
// contains HdlParserArchitectureDefinitions.
class HdlFile;

class HdlParserEntityDefinition
{
public:
    static QList<HdlParserEntityDefinition> parseText(const QStringRef text, HdlFile& file, int startingLine);

    QString name() const;
    HdlFile& file() const;
    int lineNum() const;

    const QList<HdlParserGenericDefinition> generics() const;
    const QList<HdlParserPortDefinition> ports() const;
    const QList<HdlParserArchitectureDefinition> architectures() const;

private:
    static const QString ENTITY_START_PATTERN;
    static const QString ENTITY_END_PATTERN;
    static const QString GENERIC_SECTION_START_PATTERN;
    static const QString PORT_SECTION_START_PATTERN;
    static const QString GENERIC_OR_PORT_SECTION_END_PATTERN;

    QString mName;
    HdlFile& mFile;
    int mLineNum;

    QList<HdlParserGenericDefinition> mGenerics;
    QList<HdlParserPortDefinition> mPorts;
    QList<HdlParserArchitectureDefinition> mArchitectures;

    HdlParserEntityDefinition(QString name, HdlFile& file, int lineNum);
};

#endif // HDLPARSERENTITYDEFINITION_H
