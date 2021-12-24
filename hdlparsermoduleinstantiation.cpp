#include "hdlparsermoduleinstantiation.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>

const QString HdlParserModuleInstantiation::ENTITY_INSTANTIATION_PATTERN = "(?<inst>[a-z][a-z0-9_]*)\\s*:\\s*entity\\s+(?<lib>[a-z][a-z0-9_]*)\\.(?<entity>[a-z][a-z0-9_]*)(?:\\((?<arch>[a-z][a-z0-9_]*)\\))?\\s+(?:port|generic)\\s+map\\s*\\(";
const QString HdlParserModuleInstantiation::PORT_MAP_START_PATTERN = "port\\s+map\\s+\\(";
const QString HdlParserModuleInstantiation::PORT_NAMED_ASSOC_PATTERN = "(?<port>[a-z][a-z0-9_]*)\\s*=>\\s*(?<signal>[a-z][a-z0-9_]*)";
const QString HdlParserModuleInstantiation::PORT_POSITIONAL_ASSOC_PATTERN = "(?<signal>[a-z][a-z0-9_]*)";
const QString HdlParserModuleInstantiation::COMPONENT_INSTANTIATION_PATTERN = "(?<inst>[a-z][a-z0-9_]*)\\s*:\\s*(?<entity>[a-z][a-z0-9_]*)\\s+(?:port|generic)\\s+map\\s*\\(";

HdlParserModuleInstantiation::HdlParserModuleInstantiation(QString inst, QString entity, QString arch, QString lib, HdlFile& file, int lineNum)
    :mInstanceName(inst), mEntityName(entity), mArchitectureName(arch), mLibraryName(lib), mFile(file), mLineNum(lineNum)
{

}

QList<HdlParserModuleInstantiation> HdlParserModuleInstantiation::parseText(const QStringRef text, HdlFile& file, int startingLine)
{
    QList<HdlParserModuleInstantiation> modules;

    QRegularExpression entityRegex(ENTITY_INSTANTIATION_PATTERN, QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatchIterator entityMatches = entityRegex.globalMatch(text);

    while (entityMatches.hasNext())
    {
        QRegularExpressionMatch m = entityMatches.next();
        HdlParserModuleInstantiation i(m.captured("inst"), m.captured("entity"), m.captured("arch"), m.captured("lib"), file, startingLine + text.left(m.capturedStart()).count('\n'));
        modules.append(i);
    }

    QRegularExpression componentRegex(COMPONENT_INSTANTIATION_PATTERN, QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatchIterator componentMatches = componentRegex.globalMatch(text);

    while (componentMatches.hasNext())
    {
        QRegularExpressionMatch m = componentMatches.next();
        HdlParserModuleInstantiation i(m.captured("inst"), m.captured("entity"), QString(), QString(), file, startingLine + text.left(m.capturedStart()).count('\n'));
        modules.append(i);
    }

    return modules;
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

HdlFile& HdlParserModuleInstantiation::file() const
{
    return mFile;
}

int HdlParserModuleInstantiation::lineNum() const
{
    return mLineNum;
}
