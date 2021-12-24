#ifndef HDLPARSERMODULEINSTANTIATION_H
#define HDLPARSERMODULEINSTANTIATION_H

#include <QStringRef>
#include <QString>
#include <QList>

// Forward declare so we can make the pointer w/o including the
// file, which would cause a circular reference because HdlFile
// contains HdlParserArchitectureDefinitions.
class HdlFile;

class HdlParserModuleInstantiation
{
public:
    static QList<HdlParserModuleInstantiation> parseText(const QStringRef text, HdlFile& file, int startingLine);

    QString instanceName() const;
    QString entityName() const;
    QString architectureName() const;
    QString libraryName() const;
    HdlFile& file() const;
    int lineNum() const;

private:
    static const QString ENTITY_INSTANTIATION_PATTERN;
    static const QString PORT_MAP_START_PATTERN;
    static const QString PORT_NAMED_ASSOC_PATTERN;
    static const QString PORT_POSITIONAL_ASSOC_PATTERN;
    static const QString COMPONENT_INSTANTIATION_PATTERN;

    QString mInstanceName;
    QString mEntityName;
    QString mArchitectureName;
    QString mLibraryName;
    HdlFile& mFile;
    int mLineNum;

    HdlParserModuleInstantiation(QString inst, QString entity, QString arch, QString lib, HdlFile& file, int lineNum);
};

#endif // HDLPARSERMODULEINSTANTIATION_H
