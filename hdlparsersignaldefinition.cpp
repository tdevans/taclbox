#include "hdlparsersignaldefinition.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>

const QString HdlParserSignalDefinition::SIGNAL_PATTERN = "signal\\s+(?<name>[a-z][a-z0-9_,\\s]*?)\\s*:\\s*(?<type>[a-z][a-z0-9_.\\s]*(?:\\([a-z0-9\\s]*\\))*)";

HdlParserSignalDefinition::HdlParserSignalDefinition(QString name, QString type, HdlFile& file, int lineNum)
    : mName(name), mType(type), mFile(file), mLineNum(lineNum)
{

}

QList<HdlParserSignalDefinition> HdlParserSignalDefinition::parseText(const QStringRef text, HdlFile& file, int startingLine)
{
    QList<HdlParserSignalDefinition> sigs;

    QRegularExpression signalRegex(SIGNAL_PATTERN, QRegularExpression::CaseInsensitiveOption);
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
                HdlParserSignalDefinition s(nt, m.captured("type"), file, startingLine + text.left(m.capturedStart()).count('\n'));
                sigs.append(s);
            }
        }
    }

    return sigs;
}

QString HdlParserSignalDefinition::name() const
{
    return mName;
}

QString HdlParserSignalDefinition::type() const
{
    return mType;
}

HdlFile& HdlParserSignalDefinition::file() const
{
    return mFile;
}

int HdlParserSignalDefinition::lineNum() const
{
    return mLineNum;
}
