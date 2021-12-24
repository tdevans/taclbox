#include "hdlparserpackageheaderdefinition.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>

const QString HdlParserPackageHeaderDefinition::PACKAGE_HEADER_START_PATTERN = "package\\s+(?<name>[a-z][a-z0-9_]*)\\s+is";

QList<HdlParserPackageHeaderDefinition> HdlParserPackageHeaderDefinition::parseText(const QStringRef text, HdlFile& file, int startingLine)
{
    QList<HdlParserPackageHeaderDefinition> pkgs;

    QRegularExpression packageStartRegex(PACKAGE_HEADER_START_PATTERN, QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatchIterator packageMatches = packageStartRegex.globalMatch(text);

    while (packageMatches.hasNext())
    {
        QRegularExpressionMatch packageMatch = packageMatches.next();
        HdlParserPackageHeaderDefinition pkg(packageMatch.captured("name"), file, startingLine + text.left(packageMatch.capturedStart()).count('\n'));
        pkgs.append(pkg);
    }

    return pkgs;
}

QString HdlParserPackageHeaderDefinition::name() const
{
    return mName;
}

HdlFile& HdlParserPackageHeaderDefinition::file() const
{
    return mFile;
}

int HdlParserPackageHeaderDefinition::lineNum() const
{
    return mLineNum;
}

HdlParserPackageBodyDefinition& HdlParserPackageHeaderDefinition::body()
{
    return mBodies.first();
}

HdlParserPackageHeaderDefinition::HdlParserPackageHeaderDefinition(QString name, HdlFile &file, int lineNum)
    :mName(name), mFile(file), mLineNum(lineNum)
{

}
