#ifndef HDLPARSERARCHITECTUREDEFINITION_H
#define HDLPARSERARCHITECTUREDEFINITION_H

#include <QString>
#include <QList>
#include "hdlparsertypedefinition.h"
#include "hdlparsersignaldefinition.h"

class HdlParserArchitectureDefinition
{
public:
    HdlParserArchitectureDefinition();
    HdlParserArchitectureDefinition(QString name, QString entityName);

    static QList<HdlParserArchitectureDefinition> parseText(const QStringRef text, QString filePath, int startingLine);

    QString name() const;
    void setName(QString name);

    QString entityName() const;
    void setEntityName(QString entityName);

    QString filePath() const;

    int lineNum() const;

    QList<HdlParserTypeDefinition> types() const;
    void addType(HdlParserTypeDefinition t);
    void removeType(HdlParserTypeDefinition t);

    QList<HdlParserSignalDefinition> sigs() const;
    void addSig(HdlParserSignalDefinition sig);
    void removeSig(HdlParserSignalDefinition sig);


private:
    static const QString ARCHITECTURE_START_PATTERN;
    static const QString ARCHITECTURE_END_PATTERN;

    QString mName;
    QString mEntityName;
    int mLineNum;
    QString mFilePath;
    QList<HdlParserTypeDefinition> mTypes;
    QList<HdlParserSignalDefinition> mSigs;

};

#endif // HDLPARSERARCHITECTUREDEFINITION_H
