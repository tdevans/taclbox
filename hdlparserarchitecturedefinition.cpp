#include "hdlparserarchitecturedefinition.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>

const QString HdlParserArchitectureDefinition::ARCHITECTURE_START_PATTERN = "architecture\\s+(?<name>[a-zA-Z][a-zA-Z0-9_]*)\\s+of\\s+(?<entity>[a-zA-Z][a-zA-Z0-9_]*)\\s+is";
const QString HdlParserArchitectureDefinition::ARCHITECTURE_END_PATTERN = "end\\s+(?:architecture\\s+)?%1;"; // Need to fill in the architecture name before matching

HdlParserArchitectureDefinition::HdlParserArchitectureDefinition()
{

}

HdlParserArchitectureDefinition::HdlParserArchitectureDefinition(QString name, QString entityName)
    : mName(name), mEntityName(entityName)
{

}

QList<HdlParserArchitectureDefinition> HdlParserArchitectureDefinition::parseText(QString text)
{
    QList<HdlParserArchitectureDefinition> architectures;

    int architectureStart = 0;
    QRegularExpression architectureStartRegex(ARCHITECTURE_START_PATTERN);
    QRegularExpressionMatch ms;
    QRegularExpressionMatch me;

    do
    {
        ms = architectureStartRegex.match(text, architectureStart);
        if (ms.hasMatch())
        {
            architectureStart = ms.capturedEnd();
            QString architectureName = ms.captured("name");
            QString architectureEntityName = ms.captured("entity");
            QRegularExpression architectureEndRegex(ARCHITECTURE_END_PATTERN.arg(architectureName));
            me = architectureEndRegex.match(text, ms.capturedStart() + ms.capturedLength());
            if (me.hasMatch())
            {
                architectureStart = me.capturedEnd();

                HdlParserArchitectureDefinition x(architectureName, architectureEntityName);

                // Get things that are inside the architecture
                QString architectureText = text.mid(ms.capturedEnd(), me.capturedStart() - ms.capturedEnd());

                x.mTypes = HdlParserTypeDefinition::parseText(architectureText);
                x.mSigs = HdlParserSignalDefinition::parseText(architectureText);

                architectures.append(x);
            }
        }

    } while(ms.hasMatch());

    return architectures;
}

QString HdlParserArchitectureDefinition::name() const
{
    return mName;
}

void HdlParserArchitectureDefinition::setName(QString name)
{
    mName = name;
}

QString HdlParserArchitectureDefinition::entityName() const
{
    return mEntityName;
}

void HdlParserArchitectureDefinition::setEntityName(QString entityName)
{
    mEntityName = entityName;
}

QList<HdlParserTypeDefinition> HdlParserArchitectureDefinition::types() const
{
    return mTypes;
}

void HdlParserArchitectureDefinition::addType(HdlParserTypeDefinition t)
{
    if (!mTypes.contains(t))
    {
        mTypes.append(t);
    }
}

void HdlParserArchitectureDefinition::removeType(HdlParserTypeDefinition t)
{
    mTypes.removeAll(t);
}

QList<HdlParserSignalDefinition> HdlParserArchitectureDefinition::sigs() const
{
    return mSigs;
}

void HdlParserArchitectureDefinition::addSig(HdlParserSignalDefinition sig)
{
    if (!mSigs.contains(sig))
    {
        mSigs.append(sig);
    }
}

void HdlParserArchitectureDefinition::removeSig(HdlParserSignalDefinition sig)
{
    mSigs.removeAll(sig);
}
