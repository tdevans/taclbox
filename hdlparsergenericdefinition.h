#ifndef HDLPARSERGENERICDEFINITION_H
#define HDLPARSERGENERICDEFINITION_H

#include <QString>
#include <QList>

// Forward declare so we can make the pointer w/o including the
// file, which would cause a circular reference because HdlFile
// contains HdlParserArchitectureDefinitions.
class HdlFile;

class HdlParserGenericDefinition
{
public:
    static QList<HdlParserGenericDefinition> parseText(const QStringRef text, HdlFile& file, int startingLine);

    bool operator==(const HdlParserGenericDefinition& other);

    QString name() const;
    void setName(QString name);

    QString type() const;
    void setType(QString type);

    HdlFile& file() const;

    int lineNum() const;

private:
    static const QString GENERIC_PATTERN;

    QString mName;
    QString mType;
    HdlFile& mFile;
    int mLineNum;

    HdlParserGenericDefinition(QString name, QString type, HdlFile& file, int lineNum);
};

#endif // HDLPARSERGENERICDEFINITION_H
