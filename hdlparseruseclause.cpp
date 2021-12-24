#include "hdlparseruseclause.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>

const QString HdlParserUseClause::USE_CLAUSE_PATTERN = "use\\s+(?<library>[a-z][a-z0-9_]*)\\.(?<package>[a-z][a-z0-9_]*)(?:\\.(?<item>[a-z][a-z0-9_]*))?";

QList<HdlParserUseClause> HdlParserUseClause::parseText(const QStringRef text, HdlFile &file, int startingLine)
{
    QList<HdlParserUseClause> uses;

    QRegularExpression useRegex(USE_CLAUSE_PATTERN, QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatchIterator useMatches = useRegex.globalMatch(text);
    while (useMatches.hasNext())
    {
        QRegularExpressionMatch m = useMatches.next();
        HdlParserUseClause u(m.captured("library"), m.captured("package"), m.captured("item"), file, startingLine + text.left(m.capturedStart()).count('\n'));
        uses.append(u);
    }

    return uses;
}

HdlFile& HdlParserUseClause::file() const
{
    return mFile;
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

HdlParserUseClause::HdlParserUseClause(QString lib, QString pkg, QString item, HdlFile &file, int lineNum)
    :mLibraryName(lib), mPackageName(pkg), mItemName(item), mFile(file), mLineNum(lineNum)
{

}
