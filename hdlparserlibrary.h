#ifndef HDLPARSERLIBRARY_H
#define HDLPARSERLIBRARY_H

#include <QString>
#include <QMap>
#include <QList>
#include "hdlparserpackageheaderdefinition.h"

class HdlParserLibrary
{
public:
    HdlParserLibrary(QString name, QString sourcePath);

    QString name() const;

    QString sourcePath() const;

    void refresh();

    bool operator==(const HdlParserLibrary& other);

    QMap<QString, QList<HdlParserPackageHeaderDefinition>>& packages();

private:
    QString mName;
    QString mSourcePath;

    // Map the package name or entity name, which must be unique in the library,
    // to the object representing that package or entity.
    QMap<QString, QList<HdlParserPackageHeaderDefinition>> mDefinesPackages;
};

#endif // HDLPARSERLIBRARY_H
