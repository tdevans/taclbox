#include "hdlparserlibrary.h"
#include "hdlparsercomments.h"
#include "hdlparserpackageheaderdefinition.h"
#include <QDir>
#include <QFile>
#include <QDebug>

HdlParserLibrary::HdlParserLibrary(QString name, QString sourcePath)
    :mName(name), mSourcePath(sourcePath)
{
}

QString HdlParserLibrary::name() const
{
    return mName;
}

QString HdlParserLibrary::sourcePath() const
{
    return mSourcePath;
}


void HdlParserLibrary::refresh()
{

}

bool HdlParserLibrary::operator==(const HdlParserLibrary &other)
{
    return ((other.mName == mName) && (other.mSourcePath == mSourcePath));
}

QMap<QString, QList<HdlParserPackageHeaderDefinition> > &HdlParserLibrary::packages()
{
    return mDefinesPackages;
}
