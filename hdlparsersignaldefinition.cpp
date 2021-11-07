#include "hdlparsersignaldefinition.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>

const QString HdlParserSignalDefinition::SIGNAL_PATTERN = "signal\\s+(?<name>[a-zA-Z][a-zA-Z0-9_,\\s]*?)\\s*:\\s*(?<type>[a-zA-Z][a-zA-Z0-9_\\s]*(?:\\([a-zA-Z0-9\\s]*\\))*)";

HdlParserSignalDefinition::HdlParserSignalDefinition()
{

}

HdlParserSignalDefinition::HdlParserSignalDefinition(QString name, QString typeName)
    : mName(name), mTypeName(typeName)
{

}

QList<HdlParserSignalDefinition> HdlParserSignalDefinition::parseText(const QStringRef text, QString filePath, int startingLine)
{
    QList<HdlParserSignalDefinition> sigs;

    QRegularExpression signalRegex(SIGNAL_PATTERN);
    QRegularExpressionMatchIterator signalMatches = signalRegex.globalMatch(text);

    while (signalMatches.hasNext())
    {
        QRegularExpressionMatch m = signalMatches.next();

        QStringList names = m.captured("name").split(",");

        for (auto& n : names)
        {
            QString nt = n.trimmed();
            if (!nt.isEmpty())
            {
                HdlParserSignalDefinition s;
                s.mName = n.trimmed();
                s.mTypeName = m.captured("type");
                s.mFilePath = filePath;
                s.mLineNum = startingLine + text.left(m.capturedStart()).count('\n');
                sigs.append(s);
            }
        }
    }

    return sigs;
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

QString HdlParserSignalDefinition::filePath() const
{
    return mFilePath;
}

int HdlParserSignalDefinition::lineNum() const
{
    return mLineNum;
}
