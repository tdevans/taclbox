#ifndef HDLPARSERTYPEDEFINITION_H
#define HDLPARSERTYPEDEFINITION_H

#include <QString>
#include <QStringList>
#include <QStringRef>
#include <QList>

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

    HdlParserTypeDefinition();
    HdlParserTypeDefinition(QString name);

    static QList<HdlParserTypeDefinition> parseText(const QStringRef text, QString filePath, int startingLine);

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

    QList<ArrayRange> arrayDimensions() const;
    QString arrayType() const;

    QString filePath() const;

    int lineNum() const;

private:
    static const QString ENUM_PATTERN;
    static const QString SCALAR_PATTERN;
    static const QString ARRAY_PATTERN;
    static const QString UNCONSTRAINED_RANGE_PATTERN;
    static const QString CONSTRAINED_RANGE_PATTERN;

    QString mName;
    QString mFilePath;
    int mLineNum;
    TypeCategory mCateogry;

    QStringList mEnumValues;

    double mRangeLeft;
    double mRangeRight;
    bool mRangeDescending;

    QList<ArrayRange> mArrayDimensions;
    QString mArrayType;

};

#endif // HDLPARSERTYPEDEFINITION_H
