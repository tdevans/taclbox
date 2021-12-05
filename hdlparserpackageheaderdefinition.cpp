#include "hdlparserpackageheaderdefinition.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>

const QString HdlParserPackageHeaderDefinition::PACKAGE_HEADER_START_PATTERN = "package\\s+(?<name>[a-z][a-z0-9_]*)\\s+is";

QList<HdlParserPackageHeaderDefinition> HdlParserPackageHeaderDefinition::parseText(const QStringRef text, QString filePath, int startingLine)
{
    QList<HdlParserPackageHeaderDefinition> pkgs;

    QRegularExpression packageStartRegex(PACKAGE_HEADER_START_PATTERN, QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatchIterator packageMatches = packageStartRegex.globalMatch(text);

    while (packageMatches.hasNext())
    {
        QRegularExpressionMatch packageMatch = packageMatches.next();
        HdlParserPackageHeaderDefinition pkg;
        pkg.mName = packageMatch.captured("name");
        pkg.mFilePath = filePath;
        pkg.mLineNum = startingLine + text.left(packageMatch.capturedStart()).count('\n');
        pkgs.append(pkg);
    }

    return pkgs;
}

QString HdlParserPackageHeaderDefinition::name() const
{
    return mName;
}

QString HdlParserPackageHeaderDefinition::filePath() const
{
    return mFilePath;
}

int HdlParserPackageHeaderDefinition::lineNum() const
{
    return mLineNum;
}

HdlParserPackageHeaderDefinition::HdlParserPackageHeaderDefinition()
{

}
