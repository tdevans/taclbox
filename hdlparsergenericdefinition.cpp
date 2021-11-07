#include "hdlparsergenericdefinition.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>
#include <QDebug>

const QString HdlParserGenericDefinition::GENERIC_PATTERN = "(?<name>[a-zA-Z][a-zA-Z0-9_]*)\\s*:\\s+(?<type>[a-zA-Z][a-zA-Z0-9_\\s]*(?:\\([a-zA-Z0-9\\s]*\\))*)";

HdlParserGenericDefinition::HdlParserGenericDefinition()
{

}

HdlParserGenericDefinition::HdlParserGenericDefinition(QString name, QString type)
    :mName(name), mType(type)
{

}

QList<HdlParserGenericDefinition> HdlParserGenericDefinition::parseText(const QStringRef text, QString filePath, int startingLine)
{
    QList<HdlParserGenericDefinition> generics;

    QRegularExpression genericRegex(GENERIC_PATTERN);
    QRegularExpressionMatchIterator genericMatches = genericRegex.globalMatch(text);

    while (genericMatches.hasNext())
    {
        QRegularExpressionMatch m = genericMatches.next();
        //qDebug() << QString("Found port %1").arg(m.captured("name"));

        HdlParserGenericDefinition g;
        g.mName = m.captured("name");
        g.mType = m.captured("type");
        g.mFilePath = filePath;
        g.mLineNum = startingLine + text.left(m.capturedStart()).count('\n');

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

QString HdlParserGenericDefinition::filePath() const
{
    return mFilePath;
}

int HdlParserGenericDefinition::lineNum() const
{
    return mLineNum;
}
