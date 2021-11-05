#include "dependencyparsergenericdefinition.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>
#include <QDebug>

const QString DependencyParserGenericDefinition::GENERIC_PATTERN = "(?<name>[a-zA-Z][a-zA-Z0-9_]*)\\s*:\\s+(?<type>[a-zA-Z][a-zA-Z0-9_\\s]*(?:\\([a-zA-Z0-9\\s]*\\))*)";

DependencyParserGenericDefinition::DependencyParserGenericDefinition()
{

}

DependencyParserGenericDefinition::DependencyParserGenericDefinition(QString name, QString type)
    :mName(name), mType(type)
{

}

QList<DependencyParserGenericDefinition> DependencyParserGenericDefinition::parseText(QString text)
{
    QList<DependencyParserGenericDefinition> generics;

    QRegularExpression genericRegex(GENERIC_PATTERN);
    QRegularExpressionMatchIterator genericMatches = genericRegex.globalMatch(text);

    while (genericMatches.hasNext())
    {
        QRegularExpressionMatch m = genericMatches.next();
        //qDebug() << QString("Found port %1").arg(m.captured("name"));

        DependencyParserGenericDefinition g;
        g.mName = m.captured("name");
        g.mType = m.captured("type");

        generics.append(g);
    }

    return generics;
}

bool DependencyParserGenericDefinition::operator==(const DependencyParserGenericDefinition &other)
{
    if ((other.mName == mName) && (other.mType == mType))
        return true;
    else
        return false;
}

QString DependencyParserGenericDefinition::name() const
{
    return mName;
}

void DependencyParserGenericDefinition::setName(QString name)
{
    mName = name;
}

QString DependencyParserGenericDefinition::type() const
{
    return mType;
}

void DependencyParserGenericDefinition::setType(QString type)
{
    mType = type;
}
