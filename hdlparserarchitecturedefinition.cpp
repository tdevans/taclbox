#include "hdlparserarchitecturedefinition.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include "hdlfile.h"

const QString HdlParserArchitectureDefinition::ARCHITECTURE_START_PATTERN = "architecture\\s+(?<name>[a-z][a-z0-9_]*)\\s+of\\s+(?<entity>[a-z][a-z0-9_]*)\\s+is";
const QString HdlParserArchitectureDefinition::ARCHITECTURE_END_PATTERN = "end\\s+(?:architecture\\s+)?%1;"; // Need to fill in the architecture name before matching

HdlParserArchitectureDefinition::HdlParserArchitectureDefinition(QString name, QString entityName, HdlFile& file, int lineNum)
    : mName(name), mEntityName(entityName), mFile(file), mLineNum(lineNum)
{

}

QList<HdlParserArchitectureDefinition> HdlParserArchitectureDefinition::parseText(const QStringRef text, HdlFile& file, int startingLine)
{
    QList<HdlParserArchitectureDefinition> architectures;

    int architectureStart = 0;
    QRegularExpression architectureStartRegex(ARCHITECTURE_START_PATTERN, QRegularExpression::CaseInsensitiveOption);
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
            QRegularExpression architectureEndRegex(ARCHITECTURE_END_PATTERN.arg(architectureName), QRegularExpression::CaseInsensitiveOption);
            me = architectureEndRegex.match(text, ms.capturedStart() + ms.capturedLength());
            if (me.hasMatch())
            {
                architectureStart = me.capturedEnd();

                // Where did we find the architecture
                int l = text.left(ms.capturedStart()).count('\n');

                HdlParserArchitectureDefinition x(architectureName, architectureEntityName, file, l + startingLine);

                // Get things that are inside the architecture
                const QStringRef architectureText = text.mid(ms.capturedEnd(), me.capturedStart() - ms.capturedEnd());

                x.mTypes = HdlParserTypeDefinition::parseText(architectureText, file, startingLine + text.left(ms.capturedEnd()).count('\n'));
                x.mSigs = HdlParserSignalDefinition::parseText(architectureText, file, startingLine + text.left(ms.capturedEnd()).count('\n'));

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

QString HdlParserArchitectureDefinition::entityName() const
{
    return mEntityName;
}

HdlFile& HdlParserArchitectureDefinition::file() const
{
    return mFile;
}

int HdlParserArchitectureDefinition::lineNum() const
{
    return mLineNum;
}

QList<HdlParserTypeDefinition> HdlParserArchitectureDefinition::types() const
{
    return mTypes;
}

QList<HdlParserSignalDefinition> HdlParserArchitectureDefinition::sigs() const
{
    return mSigs;
}
