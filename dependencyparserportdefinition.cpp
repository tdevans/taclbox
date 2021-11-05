#include "dependencyparserportdefinition.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>
#include <QDebug>

const QString DependencyParserPortDefinition::PORT_PATTERN = "(?<name>[a-zA-Z][a-zA-Z0-9_]*)\\s*:\\s*(?<dir>in|out|inout)\\s+(?<type>[a-zA-Z][a-zA-Z0-9_\\s]*(?:\\([a-zA-Z0-9\\s]*\\))*)";

DependencyParserPortDefinition::DependencyParserPortDefinition()
{

}

DependencyParserPortDefinition::DependencyParserPortDefinition(QString name, ePortDir dir, QString type)
    :mName(name), mDir(dir), mType(type)
{

}

QList<DependencyParserPortDefinition> DependencyParserPortDefinition::parseText(QString text)
{
    QList<DependencyParserPortDefinition> ports;

    QRegularExpression portRegex(PORT_PATTERN);
    QRegularExpressionMatchIterator portMatches = portRegex.globalMatch(text);

    while (portMatches.hasNext())
    {
        QRegularExpressionMatch m = portMatches.next();
        //qDebug() << QString("Found port %1").arg(m.captured("name"));

        DependencyParserPortDefinition p;
        p.mName = m.captured("name");
        p.mType = m.captured("type");

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

bool DependencyParserPortDefinition::operator==(const DependencyParserPortDefinition &other)
{
    if ((other.mType == mType) && (other.mDir == mDir) && (other.mType == mType))
        return true;
    else
        return false;
}

QString DependencyParserPortDefinition::name() const
{
    return mName;
}

void DependencyParserPortDefinition::setName(QString name)
{
    mName = name;
}

ePortDir DependencyParserPortDefinition::dir() const
{
    return mDir;
}

QString DependencyParserPortDefinition::dirString() const
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

void DependencyParserPortDefinition::setDir(ePortDir dir)
{
    mDir = dir;
}

QString DependencyParserPortDefinition::type() const
{
    return mType;
}

void DependencyParserPortDefinition::setType(QString type)
{
    mType = type;
}
