#ifndef HDLPARSERPACKAGEBODYDEFINITION_H
#define HDLPARSERPACKAGEBODYDEFINITION_H

#include <QString>
#include <QStringRef>
#include <QList>

class HdlParserPackageBodyDefinition
{
public:
    static QList<HdlParserPackageBodyDefinition> parseText(const QStringRef text, QString filePath, int startingLine);

    QString name() const;
    QString filePath() const;
    int lineNum() const;

private:
    static const QString PACKAGE_BODY_START_PATTERN;

    QString mName;
    QString mFilePath;
    int mLineNum;

    HdlParserPackageBodyDefinition();
};

#endif // HDLPARSERPACKAGEBODYDEFINITION_H
