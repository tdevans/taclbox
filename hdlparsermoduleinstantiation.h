#ifndef HDLPARSERMODULEINSTANTIATION_H
#define HDLPARSERMODULEINSTANTIATION_H

#include <QStringRef>
#include <QString>
#include <QList>

class HdlParserModuleInstantiation
{
public:
    HdlParserModuleInstantiation();

    static QList<HdlParserModuleInstantiation> parseText(const QStringRef text, QString filePath, int startingLine);

    bool operator==(const HdlParserModuleInstantiation& other) const;

    QString instanceName() const;
    QString entityName() const;
    QString architectureName() const;
    QString libraryName() const;
    QString filePath() const;
    int lineNum() const;

private:
    static const QString ENTITY_INSTANTIATION_PATTERN;
    static const QString PORT_MAP_START_PATTERN;
    static const QString PORT_NAMED_ASSOC_PATTERN;
    static const QString PORT_POSITIONAL_ASSOC_PATTERN;

    QString mInstanceName;
    QString mEntityName;
    QString mArchitectureName;
    QString mLibraryName;
    QString mFilePath;
    int mLineNum;
};

#endif // HDLPARSERMODULEINSTANTIATION_H
