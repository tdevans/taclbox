#ifndef HDLPARSERPACKAGEHEADERDEFINITION_H
#define HDLPARSERPACKAGEHEADERDEFINITION_H

#include <QList>
#include <QStringRef>
#include <QString>

class HdlParserPackageHeaderDefinition
{
public:
    static QList<HdlParserPackageHeaderDefinition> parseText(const QStringRef text, QString filePath, int startingLine);

private:
    static const QString PACKAGE_HEADER_START_PATTERN;

    QString mName;
    QString mFilePath;
    int mLineNum;

    HdlParserPackageHeaderDefinition();
};

#endif // HDLPARSERPACKAGEHEADERDEFINITION_H
