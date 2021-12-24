#ifndef HDLPARSERPACKAGEBODYDEFINITION_H
#define HDLPARSERPACKAGEBODYDEFINITION_H

#include <QString>
#include <QStringRef>
#include <QList>

// Forward declare so we can make the pointer w/o including the
// file, which would cause a circular reference because HdlFile
// contains HdlParserArchitectureDefinitions.
class HdlFile;

class HdlParserPackageBodyDefinition
{
public:
    static QList<HdlParserPackageBodyDefinition> parseText(const QStringRef text, HdlFile& file, int startingLine);

    QString name() const;
    HdlFile& file() const;
    int lineNum() const;

private:
    static const QString PACKAGE_BODY_START_PATTERN;

    QString mName;
    HdlFile& mFile;
    int mLineNum;

    HdlParserPackageBodyDefinition(QString name, HdlFile& file, int lineNum);
};

#endif // HDLPARSERPACKAGEBODYDEFINITION_H
