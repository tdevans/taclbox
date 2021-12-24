#ifndef HDLPARSERPACKAGEHEADERDEFINITION_H
#define HDLPARSERPACKAGEHEADERDEFINITION_H

#include <QList>
#include <QStringRef>
#include <QString>
#include "hdlparserpackagebodydefinition.h"

// Forward declare so we can make the pointer w/o including the
// file, which would cause a circular reference because HdlFile
// contains HdlParserArchitectureDefinitions.
class HdlFile;

class HdlParserPackageHeaderDefinition
{
public:
    static QList<HdlParserPackageHeaderDefinition> parseText(const QStringRef text, HdlFile& file, int startingLine);

    QString name() const;
    HdlFile& file() const;
    int lineNum() const;

    HdlParserPackageBodyDefinition& body();

private:
    static const QString PACKAGE_HEADER_START_PATTERN;

    QString mName;
    HdlFile& mFile;
    int mLineNum;

    // Store a list of package bodies in-case we find multiple
    // bodies for this package. Then we can detect that case and
    // tell the user about the conflict.
    QList<HdlParserPackageBodyDefinition> mBodies;

    HdlParserPackageHeaderDefinition(QString name, HdlFile& file, int lineNum);
};

#endif // HDLPARSERPACKAGEHEADERDEFINITION_H
