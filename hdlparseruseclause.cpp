#include "hdlparseruseclause.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>

const QString HdlParserUseClause::USE_CLAUSE_PATTERN = "use\\s+(?<library>[a-z][a-z0-9_]*)\\.(?<package>[a-z][a-z0-9_]*)(?:\\.(?<item>[a-z][a-z0-9_]*))?";

QList<HdlParserUseClause> HdlParserUseClause::parseText(const QStringRef text, QString filePath, int startingLine)
{
    QList<HdlParserUseClause> uses;

    QRegularExpression useRegex(USE_CLAUSE_PATTERN, QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatchIterator useMatches = useRegex.globalMatch(text);
    while (useMatches.hasNext())
    {
        QRegularExpressionMatch m = useMatches.next();
        HdlParserUseClause u;
        u.mFilePath = filePath;
        u.mLineNum = startingLine + text.left(m.capturedStart()).count('\n');
        u.mLibraryName = m.captured("library");
        u.mPackageName = m.captured("package");
        u.mItemName = m.captured("item");
        uses.append(u);
    }

    return uses;
}

QString HdlParserUseClause::filePath() const
{
    return mFilePath;
}

int HdlParserUseClause::lineNum() const
{
    return mLineNum;
}

QString HdlParserUseClause::libraryName() const
{
    return mLibraryName;
}

QString HdlParserUseClause::packageName() const
{
    return mPackageName;
}

QString HdlParserUseClause::itemName() const
{
    return mItemName;
}

HdlParserUseClause::HdlParserUseClause()
{

}
