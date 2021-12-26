#include "project.h"
#include <QRegularExpression>
#include <QStringList>

Project::Project(QString filePath, QObject *parent)
    :QObject(parent), mProjectFile(QFileInfo(filePath))
{

}

QString Project::name() const
{
    return mName;
}

void Project::setName(QString name)
{
    mName = name;
}

SemanticVersion Project::version() const
{
    return mProjectVersion;
}

void Project::setVersion(SemanticVersion version)
{
    mProjectVersion = version;
}

SemanticVersion Project::taclVersion() const
{
    return mTaclVersion;
}

void Project::setTaclVersion(SemanticVersion version)
{
    mTaclVersion = version;
}

QFileInfo Project::file() const
{
    return mProjectFile;
}

QString Project::sourceLibName() const
{
    return makeLibName(mName, mProjectVersion);
}

QString Project::testLibName() const
{
    return makeTestLibName(mName, mProjectVersion);
}

QDir Project::sourceDir() const
{
    QDir pd = mProjectFile.dir();
    pd.cd("source");
    return pd;
}

QDir Project::simulationDir() const
{
    QDir sd = mProjectFile.dir();
    sd.cd("simulation");
    return sd;
}

QDir Project::testbenchDir() const
{
    QDir td = simulationDir();
    td.cd("testbench");
    return td;
}

const QList<HdlFile>& Project::sourceFiles() const
{
    return mSourceFiles;
}

const QList<HdlFile>& Project::testbenchFiles() const
{
    return mTestbenchFiles;
}

void Project::initializeSourceWatcher()
{
    mSourceWatcher = new QFileSystemWatcher(this);
    if ((mSourceWatcher) && (sourceDir().exists()))
    {
        mSourceWatcher->addPath(sourceDir().canonicalPath());
        connect(mSourceWatcher, &QFileSystemWatcher::directoryChanged, this, &Project::refreshSourceFiles);
    }
}

void Project::initializeTestbenchWatcher()
{
    mTestbenchWatcher = new QFileSystemWatcher(this);
    if ((mTestbenchWatcher) && (testbenchDir().exists()))
    {
        mTestbenchWatcher->addPath(testbenchDir().canonicalPath());
        connect(mTestbenchWatcher, &QFileSystemWatcher::directoryChanged, this, &Project::refreshTestbenchFiles);
    }
}

QString Project::makeLibName(QString prjName, SemanticVersion prjVersion) const
{
    return libifyString(prjName + QString("_lib_v%1_%2_%3").arg(prjVersion.major()).arg(prjVersion.minor()).arg(prjVersion.patch()));
}

QString Project::makeTestLibName(QString prjName, SemanticVersion prjVersion) const
{
    return libifyString(prjName + QString("_test_lib_v%1_%2_%3").arg(prjVersion.major()).arg(prjVersion.minor()).arg(prjVersion.patch()));
}

QString Project::libifyString(QString str) const
{
    return str.toLower().replace(QRegularExpression("[^a-z0-9]+"), "_");
}

void Project::refreshSourceFiles()
{
    QStringList vhdlFiles = sourceDir().entryList(QStringList("*.vhd"), QDir::Files);
    bool changed = false;

    // Remove any source files that no longer exist
    QList<HdlFile> existingFiles;
    for (auto& x : mSourceFiles)
    {
        if (vhdlFiles.contains(x.fileName()))
        {
            existingFiles.append(x);
        }
        else
        {
            changed = true;
        }
    }

    if (changed)
    {
        mSourceFiles = existingFiles;
    }

    // Add or update files
    for (auto& x : vhdlFiles)
    {
        int existingIndex = -1;
        for (int i = 0; i < mSourceFiles.size(); ++i)
        {
            if (mSourceFiles[i].fileName() == x)
            {
                existingIndex = i;
                break;
            }
        }

        if (existingIndex < 0)
        {
            // A new file was added
            qDebug() << QString("Source file added: %1").arg(sourceDir().filePath(x));
            HdlFile f(sourceDir().filePath(x));
            if (!f.isNull())
            {
                mSourceFiles.append(f);
                changed = true;
            }
        }
        else
        {
            // The file already exists
            // check if it has been modified
            QFileInfo f(sourceDir().filePath(x));
            if (mSourceFiles[existingIndex].parseTime() < f.lastModified())
            {
                qDebug() << QString("Source file modified: %1").arg(f.filePath());
                HdlFile g(f.filePath());
                if (!g.isNull())
                {
                    mSourceFiles[existingIndex] = g;
                    changed = true;
                }
            }
        }
    }

    if (changed)
    {
        qDebug() << "Source files changed";
        emit sourceFilesUpdated();
    }
}

void Project::refreshTestbenchFiles()
{

}
