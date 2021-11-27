#include "hdlparsermoduleinstantiation.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>

const QString HdlParserModuleInstantiation::ENTITY_INSTANTIATION_PATTERN = "(?<inst>[a-zA-Z][a-zA-Z0-9_]*)\\s*:\\s*entity\\s+(?<lib>[a-zA-Z][a-zA-Z0-9_]*)\\.(?<entity>[a-zA-Z][a-zA-Z0-9_]*)(?:\\((?<arch>[a-zA-Z][a-zA-Z0-9_]*)\\))?";
const QString HdlParserModuleInstantiation::PORT_MAP_START_PATTERN = "port\\s+map\\s+\\(";
const QString HdlParserModuleInstantiation::PORT_NAMED_ASSOC_PATTERN = "(?<port>[a-zA-Z][a-zA-Z0-9_]*)\\s*=>\\s*(?<signal>[a-zA-Z][a-zA-Z0-9_]*)";
const QString HdlParserModuleInstantiation::PORT_POSITIONAL_ASSOC_PATTERN = "(?<signal>[a-zA-Z][a-zA-Z0-9_]*)";

HdlParserModuleInstantiation::HdlParserModuleInstantiation()
{

}

QList<HdlParserModuleInstantiation> HdlParserModuleInstantiation::parseText(const QStringRef text, QString filePath, int startingLine)
{
    QList<HdlParserModuleInstantiation> modules;

    QRegularExpression entityRegex(ENTITY_INSTANTIATION_PATTERN);
    QRegularExpressionMatchIterator entityMatches = entityRegex.globalMatch(text);

    while (entityMatches.hasNext())
    {
        QRegularExpressionMatch m = entityMatches.next();

        HdlParserModuleInstantiation i;
        i.mInstanceName = m.captured("inst");
        i.mEntityName = m.captured("entity");
        i.mLibraryName = m.captured("lib");
        i.mArchitectureName = m.captured("arch"); //Note: captured() will return a null string if there was no architecture substring, which is what we'd use to represent no architeecture anyways
        i.mFilePath = filePath;
        i.mLineNum = startingLine + text.left(m.capturedStart()).count('\n');

        modules.append(i);
    }

    return modules;
}

bool HdlParserModuleInstantiation::operator==(const HdlParserModuleInstantiation &other) const
{
    return ((mInstanceName == other.mInstanceName) && (mEntityName == other.mEntityName) && (mArchitectureName == other.mArchitectureName) && (mLibraryName == other.mLibraryName) && (mFilePath == other.mFilePath) && (mLineNum == other.mLineNum));
}

QString HdlParserModuleInstantiation::instanceName() const
{
    return mInstanceName;
}

QString HdlParserModuleInstantiation::architectureName() const
{
    return mArchitectureName;
}

QString HdlParserModuleInstantiation::entityName() const
{
    return mEntityName;
}

QString HdlParserModuleInstantiation::libraryName() const
{
    return mLibraryName;
}

QString HdlParserModuleInstantiation::filePath() const
{
    return mFilePath;
}

int HdlParserModuleInstantiation::lineNum() const
{
    return mLineNum;
}
