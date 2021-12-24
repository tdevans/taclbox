#ifndef HDLPARSERUSECLAUSE_H
#define HDLPARSERUSECLAUSE_H

#include <QString>
#include <QList>
#include <QStringRef>

// Forward declare so we can make the pointer w/o including the
// file, which would cause a circular reference because HdlFile
// contains HdlParserArchitectureDefinitions.
class HdlFile;

class HdlParserUseClause
{
public:
    static QList<HdlParserUseClause> parseText(const QStringRef text, HdlFile& file, int startingLine);

    HdlFile& file() const;

    int lineNum() const;

    QString libraryName() const;
    QString packageName() const;
    QString itemName() const;

private:
    static const QString USE_CLAUSE_PATTERN;

    QString mLibraryName;
    QString mPackageName;
    QString mItemName;
    HdlFile& mFile;
    int mLineNum;

    HdlParserUseClause(QString lib, QString pkg, QString item, HdlFile& file, int lineNum);
};

#endif // HDLPARSERUSECLAUSE_H
