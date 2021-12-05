#include "hdlparserportdefinition.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>
#include <QDebug>

const QString HdlParserPortDefinition::PORT_PATTERN = "(?<name>[a-z][a-z0-9_]*)\\s*:\\s*(?<dir>in|out|inout)\\s+(?<type>[a-z][a-z0-9_\\s]*(?:\\([a-z0-9\\s]*\\))*)";

HdlParserPortDefinition::HdlParserPortDefinition()
{

}

HdlParserPortDefinition::HdlParserPortDefinition(QString name, ePortDir dir, QString type)
    :mName(name), mDir(dir), mType(type)
{

}

QList<HdlParserPortDefinition> HdlParserPortDefinition::parseText(const QStringRef text, QString filePath, int startingLine)
{
    QList<HdlParserPortDefinition> ports;

    QRegularExpression portRegex(PORT_PATTERN, QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatchIterator portMatches = portRegex.globalMatch(text);

    while (portMatches.hasNext())
    {
        QRegularExpressionMatch m = portMatches.next();
        //qDebug() << QString("Found port %1").arg(m.captured("name"));

        HdlParserPortDefinition p;
        p.mName = m.captured("name");
        p.mType = m.captured("type");
        p.mFilePath = filePath;
        p.mLineNum = startingLine + text.left(m.capturedStart()).count('\n');

        if (m.captured("dir").toLower() == "in")
        {
            p.mDir = IN;
        }
        else if (m.captured("dir").toLower() == "out")
        {
            p.mDir = OUT;
        }
        else if (m.captured("dir").toLower() == "inout")
        {
            p.mDir = BIDIR;
        }
        else
        {
            qDebug() << QString("Unrecognized port of type %1").arg(m.captured("dir"));
            continue;
        }

        ports.append(p);
    }

    return ports;
}

bool HdlParserPortDefinition::operator==(const HdlParserPortDefinition &other)
{
    if ((other.mType == mType) && (other.mDir == mDir) && (other.mType == mType))
        return true;
    else
        return false;
}

QString HdlParserPortDefinition::name() const
{
    return mName;
}

void HdlParserPortDefinition::setName(QString name)
{
    mName = name;
}

ePortDir HdlParserPortDefinition::dir() const
{
    return mDir;
}

QString HdlParserPortDefinition::dirString() const
{
    switch (mDir)
    {
    case IN:
        return QString("In");
        break;
    case OUT:
        return QString("Out");
        break;
    case BIDIR:
        return QString("BiDir");
        break;
    }
}

void HdlParserPortDefinition::setDir(ePortDir dir)
{
    mDir = dir;
}

QString HdlParserPortDefinition::type() const
{
    return mType;
}

void HdlParserPortDefinition::setType(QString type)
{
    mType = type;
}

QString HdlParserPortDefinition::filePath() const
{
    return mFilePath;
}

int HdlParserPortDefinition::lineNum() const
{
    return mLineNum;
}
