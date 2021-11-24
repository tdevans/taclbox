#ifndef PROJECT_H
#define PROJECT_H

#include <QString>
#include "semanticversion.h"

class Project
{
public:
    Project();

    QString name() const;
    void setName(QString name);

    SemanticVersion version() const;
    void setVersion(SemanticVersion version);

    SemanticVersion taclVersion() const;
    void setTaclVersion(SemanticVersion version);

    QString file() const;
    void setFile(QString filepath);

private:
    QString mProjectFile;
    QString mName;
    SemanticVersion mTaclVersion;
    SemanticVersion mProjectVersion;
};

#endif // PROJECT_H
