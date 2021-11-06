#include "hdlparserentitydefinition.h"
#include <QRegularExpression>
#include <QDebug>

const QString HdlParserEntityDefinition::ENTITY_START_PATTERN = "entity\\s+(?<name>[a-zA-Z]\\w*)\\s+is"; // Capture group grabs the entity name
const QString HdlParserEntityDefinition::ENTITY_END_PATTERN = "end\\s+(?:entity\\s+)?%1;"; // Make entity name variable here, to be filled in when we start the entity
const QString HdlParserEntityDefinition::GENERIC_SECTION_START_PATTERN = "generic\\s*\\(";
const QString HdlParserEntityDefinition::PORT_SECTION_START_PATTERN = "port\\s*\\(";
const QString HdlParserEntityDefinition::GENERIC_OR_PORT_SECTION_END_PATTERN = "\\);";


HdlParserEntityDefinition::HdlParserEntityDefinition()
{

}

HdlParserEntityDefinition::HdlParserEntityDefinition(QString name)
    :mName(name)
{

}

QList<HdlParserEntityDefinition> HdlParserEntityDefinition::parseText(QString text)
{
    QList<HdlParserEntityDefinition> e;

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

                HdlParserEntityDefinition x(entityName);

                QString entityDeclaration = text.mid(ms.capturedStart(), me.capturedEnd() - ms.capturedStart());

                gs = genericSectionStartRegex.match(entityDeclaration);
                ps = portSectionStartRegex.match(entityDeclaration);
                if (gs.hasMatch())
                {
                    if (ps.hasMatch())
                    {
                        x.mGenerics = HdlParserGenericDefinition::parseText(entityDeclaration.mid(gs.capturedEnd(), ps.capturedStart() - gs.capturedEnd()));
                    }
                    else
                    {
                        x.mGenerics = HdlParserGenericDefinition::parseText(entityDeclaration.mid(gs.capturedEnd(), me.capturedStart() - gs.capturedEnd()));
                    }
                }

                if (ps.hasMatch())
                {
                    x.mPorts = HdlParserPortDefinition::parseText(entityDeclaration.mid(ps.capturedEnd(), me.capturedStart() - ps.capturedEnd()));
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

void HdlParserEntityDefinition::setName(QString n)
{
    mName = n;
}

QList<HdlParserGenericDefinition> HdlParserEntityDefinition::generics() const
{
    return mGenerics;
}

void HdlParserEntityDefinition::setGenerics(QList<HdlParserGenericDefinition> genericList)
{
    mGenerics = genericList;
}

void HdlParserEntityDefinition::addGeneric(HdlParserGenericDefinition generic)
{
    if (!mGenerics.contains(generic))
    {
        mGenerics.append(generic);
    }
}

void HdlParserEntityDefinition::addGeneric(QString name, QString type)
{
    HdlParserGenericDefinition g(name, type);
    addGeneric(g);
}

void HdlParserEntityDefinition::removeGeneric(HdlParserGenericDefinition generic)
{
    mGenerics.removeAll(generic);
}

void HdlParserEntityDefinition::removeGeneric(QString name)
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

QList<HdlParserPortDefinition> HdlParserEntityDefinition::ports() const
{
    return mPorts;
}

void HdlParserEntityDefinition::setPorts(QList<HdlParserPortDefinition> portList)
{
    mPorts = portList;
}

void HdlParserEntityDefinition::addPort(HdlParserPortDefinition port)
{
    if (!mPorts.contains(port))
    {
        mPorts.append(port);
    }
}

void HdlParserEntityDefinition::addPort(QString name, ePortDir dir, QString type)
{
    HdlParserPortDefinition p(name, dir, type);
    addPort(p);
}

void HdlParserEntityDefinition::removePort(HdlParserPortDefinition port)
{
    mPorts.removeAll(port);
}

void HdlParserEntityDefinition::removePort(QString name)
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
