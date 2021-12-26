#include "hdlfile.h"
#include <QFile>
#include "hdlparsercomments.h"

HdlFile::HdlFile(QString filePath)
    :mNull(true)
{
    mFileInfo = QFileInfo(filePath);
    QFile f(mFileInfo.filePath());
    if (f.open(QIODevice::ReadOnly))
    {
        QString rawFile = f.readAll();
        mParseTime = QDateTime::currentDateTimeUtc();
        QString noComments = removeComments(rawFile);
        QStringRef noCommentsRef(&noComments);
        mPackageHeaders = HdlParserPackageHeaderDefinition::parseText(noCommentsRef, *this, 0);
        mPackageBodies = HdlParserPackageBodyDefinition::parseText(noCommentsRef, *this, 0);
        mEntities = HdlParserEntityDefinition::parseText(noCommentsRef, *this, 0);
        mArchitectures = HdlParserArchitectureDefinition::parseText(noCommentsRef, *this, 0);
        mUseClauses = HdlParserUseClause::parseText(noCommentsRef, *this, 0);
        mNull = false;
    }
}

bool HdlFile::isNull() const
{
    return mNull;
}

QString HdlFile::filePath() const
{
    return mFileInfo.absoluteFilePath();
}

QString HdlFile::fileName() const
{
    return mFileInfo.fileName();
}

const QFileInfo &HdlFile::fileInfo() const
{
    return mFileInfo;
}

QDateTime HdlFile::parseTime() const
{
    return mParseTime;
}

const QList<HdlParserPackageHeaderDefinition>& HdlFile::packageHeaders() const
{
    return mPackageHeaders;
}

const QList<HdlParserPackageBodyDefinition>& HdlFile::packageBodies() const
{
    return mPackageBodies;
}

const QList<HdlParserEntityDefinition>& HdlFile::entities() const
{
    return mEntities;
}

const QList<HdlParserArchitectureDefinition> &HdlFile::architectures() const
{
    return mArchitectures;
}

const QList<HdlParserUseClause> &HdlFile::useClauses() const
{
    return mUseClauses;
}
