#ifndef HDLPARSERTYPEDEFINITION_H
#define HDLPARSERTYPEDEFINITION_H

#include <QString>
#include <QStringList>
#include <QList>

class HdlParserTypeDefinition
{
public:
    enum TypeCategory {SCALAR, ENUM, PHYSICAL, ARRAY, STRUCT};

    HdlParserTypeDefinition();
    HdlParserTypeDefinition(QString name);

    static QList<HdlParserTypeDefinition> parseText(QString text);

    bool operator==(const HdlParserTypeDefinition& other);

    TypeCategory category() const;
    void setCateogry(TypeCategory c);

    QString name() const;
    void setName(QString name);

    QStringList enumValues() const;
    void setEnumValues(QStringList ev);
    void addEnumValue(QString v);
    void removeEnumValue(QString v);

    double rangeLeft() const;
    double rangeRight() const;
    bool rangeDescending() const;

private:
    static const QString ENUM_PATTERN;
    static const QString SCALAR_PATTERN;

    QString mName;
    TypeCategory mCateogry;

    QStringList mEnumValues;

    double mRangeLeft;
    double mRangeRight;
    bool mRangeDescending;

};

#endif // HDLPARSERTYPEDEFINITION_H
