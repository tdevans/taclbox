#ifndef PROJECT_H
#define PROJECT_H

#include <QObject>
#include <QString>
#include <QDir>
#include <QFileSystemWatcher>
#include <QJsonObject>
#include "semanticversion.h"
#include "hdlfile.h"

class Project : public QObject
{
    Q_OBJECT

public:
    Project(QString filePath, QObject* parent = nullptr);

    QString name() const;
    void setName(QString name);

    SemanticVersion version() const;
    void setVersion(SemanticVersion version);

    SemanticVersion taclVersion() const;
    void setTaclVersion(SemanticVersion version);

    QFileInfo file() const;

    QString sourceLibName() const;
    QString testLibName() const;

    QDir sourceDir() const;
    QDir simulationDir() const;
    QDir testbenchDir() const;

    const QList<HdlFile>& sourceFiles() const;
    const QList<HdlFile>& testbenchFiles() const;

private:
    QFileInfo mProjectFile;
    QString mName;
    SemanticVersion mTaclVersion;
    SemanticVersion mProjectVersion;

    QList<HdlFile> mSourceFiles;
    QList<HdlFile> mTestbenchFiles;

    QFileSystemWatcher* mSourceWatcher;
    QFileSystemWatcher* mTestbenchWatcher;

    void initializeSourceWatcher();
    void initializeTestbenchWatcher();

    QString makeLibName(QString prjName, SemanticVersion prjVersion) const;
    QString makeTestLibName(QString prjName, SemanticVersion prjVersion) const;
    QString libifyString(QString str) const;

public slots:
    void refreshSourceFiles();
    void refreshTestbenchFiles();

signals:
    void sourceFilesUpdated();
    void testbenchFilesUpdated();
};

#endif // PROJECT_H
