#ifndef PROJECT_H
#define PROJECT_H

#include <QString>
#include <QJsonObject>
#include "semanticversion.h"

class Project
{
public:
    Project();

    static Project load(QString projectFile);

    bool save();
    bool save(QString projectFile);

    SemanticVersion version() const;
    void setVersion(SemanticVersion version);

private:
    QString mProjectFile;
    SemanticVersion mVersion;

    static SemanticVersion parseTaclVersion(QJsonObject prj);
    static SemanticVersion parseProjectVersion(QJsonObject prj);
};

#endif // PROJECT_H
