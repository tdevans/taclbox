#ifndef HDLPARSERUSECLAUSE_H
#define HDLPARSERUSECLAUSE_H

#include <QString>
#include <QList>
#include <QStringRef>

class HdlParserUseClause
{
public:
    static QList<HdlParserUseClause> parseText(const QStringRef text, QString filePath, int startingLine);

    QString filePath() const;

    int lineNum() const;

    QString libraryName() const;
    QString packageName() const;
    QString itemName() const;

private:
    static const QString USE_CLAUSE_PATTERN;

    QString mFilePath;
    int mLineNum;
    QString mLibraryName;
    QString mPackageName;
    QString mItemName;

    HdlParserUseClause();
};

#endif // HDLPARSERUSECLAUSE_H
