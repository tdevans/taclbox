#include "hdlparsergenericdefinition.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>
#include <QDebug>

const QString HdlParserGenericDefinition::GENERIC_PATTERN = "(?<name>[a-z][a-z0-9_]*)\\s*:\\s+(?<type>[a-z][a-z0-9_\\s]*(?:\\([a-z0-9\\s]*\\))*)";

HdlParserGenericDefinition::HdlParserGenericDefinition(QString name, QString type, HdlFile& file, int lineNum)
    :mName(name), mType(type), mFile(file), mLineNum(lineNum)
{

}

QList<HdlParserGenericDefinition> HdlParserGenericDefinition::parseText(const QStringRef text, HdlFile& file, int startingLine)
{
    QList<HdlParserGenericDefinition> generics;

    QRegularExpression genericRegex(GENERIC_PATTERN, QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatchIterator genericMatches = genericRegex.globalMatch(text);

    while (genericMatches.hasNext())
    {
        QRegularExpressionMatch m = genericMatches.next();
        HdlParserGenericDefinition g(m.captured("name"), m.captured("type"), file, startingLine + text.left(m.capturedStart()).count('\n'));
        generics.append(g);
    }

    return generics;
}

bool HdlParserGenericDefinition::operator==(const HdlParserGenericDefinition &other)
{
    if ((other.mName == mName) && (other.mType == mType))
        return true;
    else
        return false;
}

QString HdlParserGenericDefinition::name() const
{
    return mName;
}

void HdlParserGenericDefinition::setName(QString name)
{
    mName = name;
}

QString HdlParserGenericDefinition::type() const
{
    return mType;
}

void HdlParserGenericDefinition::setType(QString type)
{
    mType = type;
}

HdlFile& HdlParserGenericDefinition::file() const
{
    return mFile;
}

int HdlParserGenericDefinition::lineNum() const
{
    return mLineNum;
}
