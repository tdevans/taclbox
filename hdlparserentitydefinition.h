#ifndef HDLPARSERENTITYDEFINITION_H
#define HDLPARSERENTITYDEFINITION_H

#include <QList>

#include "hdlparsergenericdefinition.h"
#include "hdlparserportdefinition.h"

class HdlParserEntityDefinition
{
public:
    HdlParserEntityDefinition();
    HdlParserEntityDefinition(QString name);

    static QList<HdlParserEntityDefinition> parseText(const QStringRef text, QString filePath, int startingLine);

    QString name() const;
    void setName(QString n);

    QString filePath() const;

    int lineNum() const;

    QList<HdlParserGenericDefinition> generics() const;
    void setGenerics(QList<HdlParserGenericDefinition> genericList);
    void addGeneric(HdlParserGenericDefinition generic);
    void addGeneric(QString name, QString type);
    void removeGeneric(HdlParserGenericDefinition generic);
    void removeGeneric(QString name);

    QList<HdlParserPortDefinition> ports() const;
    void setPorts(QList<HdlParserPortDefinition> portList);
    void addPort(HdlParserPortDefinition port);
    void addPort(QString name, ePortDir dir, QString type);
    void removePort(HdlParserPortDefinition port);
    void removePort(QString name);

private:
    static const QString ENTITY_START_PATTERN;
    static const QString ENTITY_END_PATTERN;
    static const QString GENERIC_SECTION_START_PATTERN;
    static const QString PORT_SECTION_START_PATTERN;
    static const QString GENERIC_OR_PORT_SECTION_END_PATTERN;

    QString mName;
    QString mFilePath;
    int mLineNum;
    QList<HdlParserGenericDefinition> mGenerics;
    QList<HdlParserPortDefinition> mPorts;

};

#endif // HDLPARSERENTITYDEFINITION_H
