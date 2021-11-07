#ifndef HDLPARSERSIGNALDEFINITION_H
#define HDLPARSERSIGNALDEFINITION_H

#include <QString>
#include <QList>

class HdlParserSignalDefinition
{
public:
    HdlParserSignalDefinition();
    HdlParserSignalDefinition(QString name, QString typeName);

    static QList<HdlParserSignalDefinition> parseText(const QStringRef text, QString filePath, int startingLine);

    bool operator==(const HdlParserSignalDefinition& other);

    QString name() const;
    void setName(QString name);

    QString typeName() const;
    void setTypeName(QString typeName);

    QString filePath() const;

    int lineNum() const;

private:
    static const QString SIGNAL_PATTERN;

    QString mName;
    QString mTypeName;
    QString mFilePath;
    int mLineNum;
};

#endif // HDLPARSERSIGNALDEFINITION_H
