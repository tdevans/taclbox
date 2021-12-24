#ifndef HDLPARSERTYPEDEFINITION_H
#define HDLPARSERTYPEDEFINITION_H

#include <QString>
#include <QStringList>
#include <QStringRef>
#include <QList>

// Forward declare so we can make the pointer w/o including the
// file, which would cause a circular reference because HdlFile
// contains HdlParserArchitectureDefinitions.
class HdlFile;

class HdlParserTypeDefinition
{
public:
    enum TypeCategory {SCALAR, ENUM, PHYSICAL, ARRAY, STRUCT};

    struct ArrayRange
    {
        bool unconstrained;
        QString typeName;
        int rangeLeft;
        int rangeRight;
        bool rangeDescending;
    };

    static QList<HdlParserTypeDefinition> parseText(const QStringRef text, HdlFile& file, int startingLine);

    QString name() const;
    HdlFile& file() const;
    int lineNum() const;

    TypeCategory category() const;
    QStringList enumValues() const;
    double rangeLeft() const;
    double rangeRight() const;
    bool rangeDescending() const;
    QList<ArrayRange> arrayDimensions() const;
    QString arrayType() const;

private:
    static const QString ENUM_PATTERN;
    static const QString SCALAR_PATTERN;
    static const QString ARRAY_PATTERN;
    static const QString UNCONSTRAINED_RANGE_PATTERN;
    static const QString CONSTRAINED_RANGE_PATTERN;

    QString mName;
    TypeCategory mCateogry;
    HdlFile& mFile;
    int mLineNum;

    QStringList mEnumValues;
    double mRangeLeft;
    double mRangeRight;
    bool mRangeDescending;
    QList<ArrayRange> mArrayDimensions;
    QString mArrayType;

    HdlParserTypeDefinition(QString name, TypeCategory category, HdlFile& file, int lineNum);
};

#endif // HDLPARSERTYPEDEFINITION_H
