#include "hdlparsersignaldefinition.h"

const QString HdlParserSignalDefinition::SIGNAL_PATTERN = "signal\\s+(?<name>[a-zA-Z][a-zA-Z0-9_]*)\\s*:\\s*(?<type>[a-zA-Z][a-zA-Z0-9_\\s]*(?:\\([a-zA-Z0-9\\s]*\\))*)";

HdlParserSignalDefinition::HdlParserSignalDefinition()
{

}

HdlParserSignalDefinition::HdlParserSignalDefinition(QString name, QString typeName)
    : mName(name), mTypeName(typeName)
{

}

QList<HdlParserSignalDefinition> HdlParserSignalDefinition::parseText(QString text)
{
    QList<HdlParserSignalDefinition> signals;

    return signals;
}

bool HdlParserSignalDefinition::operator==(const HdlParserSignalDefinition &other)
{
    return ((other.mName == mName) && (other.mTypeName == mTypeName));
}

QString HdlParserSignalDefinition::name() const
{
    return mName;
}

void HdlParserSignalDefinition::setName(QString name)
{
    mName = name;
}

QString HdlParserSignalDefinition::typeName() const
{
    return mTypeName;
}

void HdlParserSignalDefinition::setTypeName(QString typeName)
{
    mTypeName = typeName;
}
