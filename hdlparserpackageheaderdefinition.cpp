#include "hdlparserpackageheaderdefinition.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>

const QString HdlParserPackageHeaderDefinition::PACKAGE_HEADER_START_PATTERN = "package\\s+(?<name>[a-zA-Z][a-zA-Z0-9_]*)\\s+is";

QList<HdlParserPackageHeaderDefinition> HdlParserPackageHeaderDefinition::parseText(const QStringRef text, QString filePath, int startingLine)
{
    QList<HdlParserPackageHeaderDefinition> pkgs;

    QRegularExpression packageStartRegex(PACKAGE_HEADER_START_PATTERN);
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

HdlParserPackageHeaderDefinition::HdlParserPackageHeaderDefinition()
{

}
