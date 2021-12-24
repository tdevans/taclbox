#ifndef HDLPARSERPORTDIRECTION_H
#define HDLPARSERPORTDIRECTION_H

#include <QString>

class HdlParserPortDirection
{
public:
    enum PortDirection {UNKNOWN, IN, OUT, BIDIR};

    HdlParserPortDirection(PortDirection dir);
    HdlParserPortDirection(QString dir);

    bool operator==(PortDirection dir) const;
    bool operator!=(PortDirection dir) const;

    bool operator==(const HdlParserPortDirection& other) const;
    bool operator!=(const HdlParserPortDirection& other) const;

    QString toString() const;

private:
    PortDirection mDir;
};

#endif // HDLPARSERPORTDIRECTION_H
