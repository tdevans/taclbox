#include "hdlparserportdefinition.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>
#include <QDebug>

const QString HdlParserPortDefinition::PORT_PATTERN = "(?<name>[a-z][a-z0-9_]*)\\s*:\\s*(?<dir>in|out|inout)\\s+(?<type>[a-z][a-z0-9_\\s]*(?:\\([a-z0-9\\s]*\\))*)";

HdlParserPortDefinition::HdlParserPortDefinition(QString name, HdlParserPortDirection dir, QString type, HdlFile& file, int lineNum)
    :mName(name), mDir(dir), mType(type), mFile(file), mLineNum(lineNum)
{

}

QList<HdlParserPortDefinition> HdlParserPortDefinition::parseText(const QStringRef text, HdlFile &file, int startingLine)
{
    QList<HdlParserPortDefinition> ports;

    QRegularExpression portRegex(PORT_PATTERN, QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatchIterator portMatches = portRegex.globalMatch(text);

    while (portMatches.hasNext())
    {
        QRegularExpressionMatch m = portMatches.next();
        HdlParserPortDefinition p(m.captured("name"), HdlParserPortDirection(m.captured("dir")), m.captured("type"), file, startingLine + text.left(m.capturedStart()).count('\n'));
        ports.append(p);
    }

    return ports;
}

QString HdlParserPortDefinition::name() const
{
    return mName;
}

HdlParserPortDirection HdlParserPortDefinition::dir() const
{
    return mDir;
}

QString HdlParserPortDefinition::type() const
{
    return mType;
}

HdlFile& HdlParserPortDefinition::file() const
{
    return mFile;
}

int HdlParserPortDefinition::lineNum() const
{
    return mLineNum;
}
