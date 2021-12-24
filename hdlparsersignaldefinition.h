#ifndef HDLPARSERSIGNALDEFINITION_H
#define HDLPARSERSIGNALDEFINITION_H

#include <QString>
#include <QList>

// Forward declare so we can make the pointer w/o including the
// file, which would cause a circular reference because HdlFile
// contains HdlParserArchitectureDefinitions.
class HdlFile;

class HdlParserSignalDefinition
{
public:
    static QList<HdlParserSignalDefinition> parseText(const QStringRef text, HdlFile& file, int startingLine);

    QString name() const;
    QString type() const;
    HdlFile& file() const;
    int lineNum() const;

private:
    static const QString SIGNAL_PATTERN;

    QString mName;
    QString mType;
    HdlFile& mFile;
    int mLineNum;

    HdlParserSignalDefinition(QString name, QString type, HdlFile& file, int lineNum);
};

#endif // HDLPARSERSIGNALDEFINITION_H
