#include "hdlparserportdirection.h"
#include <QDebug>

HdlParserPortDirection::HdlParserPortDirection(PortDirection dir)
    :mDir(dir)
{

}

HdlParserPortDirection::HdlParserPortDirection(QString dir)
    :mDir(UNKNOWN)
{
    if (dir.toLower() == "in")
    {
        mDir = IN;
    }
    else if (dir.toLower() == "out")
    {
        mDir = OUT;
    }
    else if (dir.toLower() == "inout")
    {
        mDir = BIDIR;
    }
    else
    {
        qDebug() << QString("Got port direction of %1 that we don't understand.").arg(dir);
        mDir = UNKNOWN;
    }
}

bool HdlParserPortDirection::operator==(PortDirection dir) const
{
    return (dir == mDir);
}

bool HdlParserPortDirection::operator!=(PortDirection dir) const
{
    return !(dir == mDir);
}

QString HdlParserPortDirection::toString() const
{
    QString s;

    switch (mDir)
    {
    case IN:
        s = "In";
        break;
    case OUT:
        s = "Out";
        break;
    case BIDIR:
        s = "BiDir";
        break;
    case UNKNOWN:
        s = "Unknown";
        break;
    default:
        s = "Unknown";
        break;
    }

    return s;
}

bool HdlParserPortDirection::operator==(const HdlParserPortDirection& other) const
{
    return (other.mDir == mDir);
}

bool HdlParserPortDirection::operator!=(const HdlParserPortDirection& other) const
{
    return (other.mDir != mDir);
}
