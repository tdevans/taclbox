#ifndef HDLPARSERGENERICDEFINITION_H
#define HDLPARSERGENERICDEFINITION_H

#include <QString>
#include <QList>

class HdlParserGenericDefinition
{
public:
    HdlParserGenericDefinition();
    HdlParserGenericDefinition(QString name, QString type);

    static QList<HdlParserGenericDefinition> parseText(const QStringRef text, QString filePath, int startingLine);

    bool operator==(const HdlParserGenericDefinition& other);

    QString name() const;
    void setName(QString name);

    QString type() const;
    void setType(QString type);

    QString filePath() const;

    int lineNum() const;

private:
    static const QString GENERIC_PATTERN;

    QString mName;
    QString mType;
    QString mFilePath;
    int mLineNum;
};

#endif // HDLPARSERGENERICDEFINITION_H
