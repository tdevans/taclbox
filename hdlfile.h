#ifndef HDLFILE_H
#define HDLFILE_H

#include <QString>
#include <QFileInfo>
#include <QList>
#include <QDateTime>

#include "hdlparserpackageheaderdefinition.h"
#include "hdlparserpackagebodydefinition.h"
#include "hdlparserentitydefinition.h"
#include "hdlparserarchitecturedefinition.h"
#include "hdlparseruseclause.h"

class HdlFile
{
public:
    HdlFile(QString filePath);

    bool isNull() const;
    QString filePath() const;
    QString fileName() const;
    const QFileInfo& fileInfo() const;
    QDateTime parseTime() const;

    const QList<HdlParserPackageHeaderDefinition>& packageHeaders() const;
    const QList<HdlParserPackageBodyDefinition>& packageBodies() const;
    const QList<HdlParserEntityDefinition>& entities() const;
    const QList<HdlParserArchitectureDefinition>& architectures() const;
    const QList<HdlParserUseClause>& useClauses() const;

    operator bool() const { return !mNull; }
private:
    bool mNull;
    QFileInfo mFileInfo;
    QDateTime mParseTime;

    QList<HdlParserPackageHeaderDefinition> mPackageHeaders;
    QList<HdlParserPackageBodyDefinition> mPackageBodies;
    QList<HdlParserEntityDefinition> mEntities;
    QList<HdlParserArchitectureDefinition> mArchitectures;
    QList<HdlParserUseClause> mUseClauses;
};

#endif // HDLFILE_H
