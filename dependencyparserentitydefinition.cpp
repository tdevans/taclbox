#include "dependencyparserentitydefinition.h"
#include <QRegularExpression>
#include <QDebug>

const QString DependencyParserEntityDefinition::ENTITY_START_PATTERN = "entity\\s+(?<name>[a-zA-Z]\\w*)\\s+is"; // Capture group grabs the entity name
const QString DependencyParserEntityDefinition::ENTITY_END_PATTERN = "end\\s+(?:entity\\s+)?%1;"; // Make entity name variable here, to be filled in when we start the entity
const QString DependencyParserEntityDefinition::GENERIC_SECTION_START_PATTERN = "generic\\s*\\(";
const QString DependencyParserEntityDefinition::PORT_SECTION_START_PATTERN = "port\\s*\\(";
const QString DependencyParserEntityDefinition::GENERIC_OR_PORT_SECTION_END_PATTERN = "\\);";


DependencyParserEntityDefinition::DependencyParserEntityDefinition()
{

}

DependencyParserEntityDefinition::DependencyParserEntityDefinition(QString name)
    :mName(name)
{

}

QList<DependencyParserEntityDefinition> DependencyParserEntityDefinition::parseText(QString text)
{
    QList<DependencyParserEntityDefinition> e;

    int entityStart = 0;
    QRegularExpression entityStartRegex(ENTITY_START_PATTERN);
    QRegularExpression genericSectionStartRegex(GENERIC_SECTION_START_PATTERN);
    QRegularExpression portSectionStartRegex(PORT_SECTION_START_PATTERN);
    QRegularExpression genericSectionEndRegex(GENERIC_OR_PORT_SECTION_END_PATTERN);
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

                DependencyParserEntityDefinition x(entityName);

                QString entityDeclaration = text.mid(ms.capturedStart(), me.capturedEnd() - ms.capturedStart());

                gs = genericSectionStartRegex.match(entityDeclaration);
                ps = portSectionStartRegex.match(entityDeclaration);
                if (gs.hasMatch())
                {
                    if (ps.hasMatch())
                    {
                        x.mGenerics = DependencyParserGenericDefinition::parseText(entityDeclaration.mid(gs.capturedEnd(), ps.capturedStart() - gs.capturedEnd()));
                    }
                    else
                    {
                        x.mGenerics = DependencyParserGenericDefinition::parseText(entityDeclaration.mid(gs.capturedEnd(), me.capturedStart() - gs.capturedEnd()));
                    }
                }

                if (ps.hasMatch())
                {
                    x.mPorts = DependencyParserPortDefinition::parseText(entityDeclaration.mid(ps.capturedEnd(), me.capturedStart() - ps.capturedEnd()));
                }

                e.append(x);
            }
        }

    } while(ms.hasMatch());


    return e;
}

QString DependencyParserEntityDefinition::name() const
{
    return mName;
}

void DependencyParserEntityDefinition::setName(QString n)
{
    mName = n;
}

QList<DependencyParserGenericDefinition> DependencyParserEntityDefinition::generics() const
{
    return mGenerics;
}

void DependencyParserEntityDefinition::setGenerics(QList<DependencyParserGenericDefinition> genericList)
{
    mGenerics = genericList;
}

void DependencyParserEntityDefinition::addGeneric(DependencyParserGenericDefinition generic)
{
    if (!mGenerics.contains(generic))
    {
        mGenerics.append(generic);
    }
}

void DependencyParserEntityDefinition::addGeneric(QString name, QString type)
{
    DependencyParserGenericDefinition g(name, type);
    addGeneric(g);
}

void DependencyParserEntityDefinition::removeGeneric(DependencyParserGenericDefinition generic)
{
    mGenerics.removeAll(generic);
}

void DependencyParserEntityDefinition::removeGeneric(QString name)
{
    QList<int> idx;

    for (int i = 0; i < mGenerics.size(); ++i)
    {
        if (mGenerics[i].name() == name)
        {
            idx.append(i);
        }
    }

    for (int i = 0; i < idx.size(); ++i)
    {
        mGenerics.removeAt(idx[i]);
    }
}

QList<DependencyParserPortDefinition> DependencyParserEntityDefinition::ports() const
{
    return mPorts;
}

void DependencyParserEntityDefinition::setPorts(QList<DependencyParserPortDefinition> portList)
{
    mPorts = portList;
}

void DependencyParserEntityDefinition::addPort(DependencyParserPortDefinition port)
{
    if (!mPorts.contains(port))
    {
        mPorts.append(port);
    }
}

void DependencyParserEntityDefinition::addPort(QString name, ePortDir dir, QString type)
{
    DependencyParserPortDefinition p(name, dir, type);
    addPort(p);
}

void DependencyParserEntityDefinition::removePort(DependencyParserPortDefinition port)
{
    mPorts.removeAll(port);
}

void DependencyParserEntityDefinition::removePort(QString name)
{
    QList<int> idx;

    for (int i = 0; i < mPorts.size(); ++i)
    {
        if (mPorts[i].name() == name)
        {
            idx.append(i);
        }
    }

    for (int i = 0; i < idx.size(); ++i)
    {
        mPorts.removeAt(idx[i]);
    }
}
