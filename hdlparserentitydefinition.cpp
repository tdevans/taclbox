#include "hdlparserentitydefinition.h"
#include <QRegularExpression>
#include <QDebug>

const QString HdlParserEntityDefinition::ENTITY_START_PATTERN = "entity\\s+(?<name>[a-z][a-z0-9_]*)\\s+is"; // Capture group grabs the entity name
const QString HdlParserEntityDefinition::ENTITY_END_PATTERN = "end\\s+(?:entity\\s+)?%1;"; // Make entity name variable here, to be filled in when we start the entity
const QString HdlParserEntityDefinition::GENERIC_SECTION_START_PATTERN = "generic\\s*\\(";
const QString HdlParserEntityDefinition::PORT_SECTION_START_PATTERN = "port\\s*\\(";
const QString HdlParserEntityDefinition::GENERIC_OR_PORT_SECTION_END_PATTERN = "\\);";

HdlParserEntityDefinition::HdlParserEntityDefinition(QString name, HdlFile& file, int lineNum)
    :mName(name), mFile(file), mLineNum(lineNum)
{

}

QList<HdlParserEntityDefinition> HdlParserEntityDefinition::parseText(const QStringRef text, HdlFile& file, int startingLine)
{
    QList<HdlParserEntityDefinition> e;

    int entityStart = 0;
    QRegularExpression entityStartRegex(ENTITY_START_PATTERN, QRegularExpression::CaseInsensitiveOption);
    QRegularExpression genericSectionStartRegex(GENERIC_SECTION_START_PATTERN, QRegularExpression::CaseInsensitiveOption);
    QRegularExpression portSectionStartRegex(PORT_SECTION_START_PATTERN, QRegularExpression::CaseInsensitiveOption);
    QRegularExpression genericSectionEndRegex(GENERIC_OR_PORT_SECTION_END_PATTERN, QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch ms;
    QRegularExpressionMatch me;
    QRegularExpressionMatch gs;
    QRegularExpressionMatch ps;

    do
    {
        ms = entityStartRegex.match(text, entityStart);
        if (ms.hasMatch())
        {
            entityStart = ms.capturedEnd();
            QString entityName = ms.captured("name");
            QRegularExpression entityEndRegex(ENTITY_END_PATTERN.arg(entityName));
            me = entityEndRegex.match(text, ms.capturedStart() + ms.capturedLength());
            if (me.hasMatch())
            {
                entityStart = me.capturedEnd();

                HdlParserEntityDefinition x(entityName, file, startingLine + text.left(ms.capturedStart()).count('\n'));

                const QStringRef entityDeclaration = text.mid(ms.capturedStart(), me.capturedEnd() - ms.capturedStart());
                int entityDeclarationLine = startingLine + text.left(ms.capturedStart()).count('\n');

                gs = genericSectionStartRegex.match(entityDeclaration);
                ps = portSectionStartRegex.match(entityDeclaration);
                if (gs.hasMatch())
                {
                    if (ps.hasMatch())
                    {
                        const QStringRef genericSection = entityDeclaration.mid(gs.capturedEnd(), ps.capturedStart() - gs.capturedEnd());
                        int genericSectionLine = entityDeclarationLine + entityDeclaration.left(gs.capturedEnd()).count('\n');
                        x.mGenerics = HdlParserGenericDefinition::parseText(genericSection, file, genericSectionLine);
                    }
                    else
                    {
                        const QStringRef genericSection = entityDeclaration.mid(gs.capturedEnd(), me.capturedStart() - gs.capturedEnd());
                        int genericSectionLine = entityDeclarationLine + entityDeclaration.left(gs.capturedEnd()).count('\n');
                        x.mGenerics = HdlParserGenericDefinition::parseText(genericSection, file, genericSectionLine);
                    }
                }

                if (ps.hasMatch())
                {
                    const QStringRef portSection = entityDeclaration.mid(ps.capturedEnd(), me.capturedStart() - ps.capturedEnd());
                    int portSectionLine = entityDeclarationLine + entityDeclaration.left(ps.capturedEnd()).count('\n');
                    x.mPorts = HdlParserPortDefinition::parseText(portSection, file, portSectionLine);
                }

                e.append(x);
            }
        }

    } while(ms.hasMatch());


    return e;
}

QString HdlParserEntityDefinition::name() const
{
    return mName;
}

HdlFile& HdlParserEntityDefinition::file() const
{
    return mFile;
}

int HdlParserEntityDefinition::lineNum() const
{
    return mLineNum;
}

const QList<HdlParserGenericDefinition> HdlParserEntityDefinition::generics() const
{
    return mGenerics;
}


const QList<HdlParserPortDefinition> HdlParserEntityDefinition::ports() const
{
    return mPorts;
}

const QList<HdlParserArchitectureDefinition> HdlParserEntityDefinition::architectures() const
{
    return mArchitectures;
}
