#include "hdlparserpackagebodydefinition.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>

const QString HdlParserPackageBodyDefinition::PACKAGE_BODY_START_PATTERN = "package\\s+body\\s+(?<name>[a-z][a-z0-9_]*)\\s+is";

QList<HdlParserPackageBodyDefinition> HdlParserPackageBodyDefinition::parseText(const QStringRef text, HdlFile& file, int startingLine)
{
    QList<HdlParserPackageBodyDefinition> pkgs;

    QRegularExpression packageBodyStartRegex(PACKAGE_BODY_START_PATTERN, QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatchIterator packageMatches = packageBodyStartRegex.globalMatch(text);

    while (packageMatches.hasNext())
    {
        QRegularExpressionMatch packageMatch = packageMatches.next();
        HdlParserPackageBodyDefinition pkg(packageMatch.captured("name"), file, startingLine + text.left(packageMatch.capturedStart()).count('\n'));
        pkgs.append(pkg);
    }

    return pkgs;
}

QString HdlParserPackageBodyDefinition::name() const
{
    return mName;
}

HdlFile& HdlParserPackageBodyDefinition::file() const
{
    return mFile;
}

int HdlParserPackageBodyDefinition::lineNum() const
{
    return mLineNum;
}

HdlParserPackageBodyDefinition::HdlParserPackageBodyDefinition(QString name, HdlFile& file, int lineNum)
    :mName(name), mFile(file), mLineNum(lineNum)
{

}
