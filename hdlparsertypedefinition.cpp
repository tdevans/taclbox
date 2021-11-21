#include "hdlparsertypedefinition.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>

const QString HdlParserTypeDefinition::ENUM_PATTERN = "type\\s+(?<name>[a-zA-Z][a-zA-Z0-9_]*)\\s+is\\s+\\((?<values>[a-zA-Z0-9_,\\s]+)\\)";
const QString HdlParserTypeDefinition::SCALAR_PATTERN = "type\\s+(?<name>[a-zA-Z][a-zA-Z0-9_]*)\\s+is\\s+range\\s+(?<left>-?[0-9]+(?:.[0-9]+)?(?:[eE]-?[0-9]+)?)\\s+(?<dir>to|downto)\\s+(?<right>-?[0-9]+(?:.[0-9]+)?(?:[eE]-?[0-9]+)?)";
const QString HdlParserTypeDefinition::ARRAY_PATTERN = "type\\s+(?<name>[a-zA-Z][a-zA-Z0-9_]*)\\s+is\\s+array\\s+\\((?<dims>[a-zA-Z0-9_\\s,<>\\-]+)\\)\\s+of\\s+(?<type>[a-zA-Z][a-zA-Z0-9_]+(?:[\\(\\)a-zA-Z0-9_\\s\\-]+)?)";
const QString HdlParserTypeDefinition::UNCONSTRAINED_RANGE_PATTERN = "(?<name>[a-zA-Z][a-zA-Z0-9_]+)\\s+range\\s+<>";
const QString HdlParserTypeDefinition::CONSTRAINED_RANGE_PATTERN = "(?<left>-?[0-9]+)\\s+(?<dir>to|downto)\\s+(?<right>-?[0-9]+)";

HdlParserTypeDefinition::HdlParserTypeDefinition()
{

}

HdlParserTypeDefinition::HdlParserTypeDefinition(QString name)
    : mName(name)
{

}

QList<HdlParserTypeDefinition> HdlParserTypeDefinition::parseText(const QStringRef text, QString filePath, int startingLine)
{
    QList<HdlParserTypeDefinition> types;

    QRegularExpression enumRegex(ENUM_PATTERN);
    QRegularExpressionMatchIterator enumMatches = enumRegex.globalMatch(text);

    while (enumMatches.hasNext())
    {
        QRegularExpressionMatch m = enumMatches.next();
        HdlParserTypeDefinition t;
        t.mName = m.captured("name");
        t.mCateogry = ENUM;
        t.mFilePath = filePath;
        t.mLineNum = startingLine + text.left(m.capturedStart()).count('\n');

        QStringList valList = m.captured("values").split(",");
        for (auto& v : valList)
        {
            t.mEnumValues.append(v.trimmed());
        }

        types.append(t);
    }


    QRegularExpression scalarRegex(SCALAR_PATTERN);
    QRegularExpressionMatchIterator scalarMatches = scalarRegex.globalMatch(text);

    while (scalarMatches.hasNext())
    {
        QRegularExpressionMatch m = scalarMatches.next();
        HdlParserTypeDefinition t;
        t.mName = m.captured("name");
        t.mCateogry = SCALAR;
        t.mFilePath = filePath;
        t.mLineNum = startingLine + text.left(m.capturedStart()).count('\n');
        t.mRangeLeft = m.captured("left").toDouble();
        t.mRangeRight = m.captured("right").toDouble();
        if (m.captured("dir") == "downto")
            t.mRangeDescending = true;
        else
            t.mRangeDescending = false;
        types.append(t);
    }


    QRegularExpression arrayRegex(ARRAY_PATTERN);
    QRegularExpression unconstrainedRegex(UNCONSTRAINED_RANGE_PATTERN);
    QRegularExpression constrainedRegex(CONSTRAINED_RANGE_PATTERN);

    QRegularExpressionMatchIterator arrayMatches = arrayRegex.globalMatch(text);

    while (arrayMatches.hasNext())
    {
        QRegularExpressionMatch m = arrayMatches.next();

        HdlParserTypeDefinition t;
        t.mName = m.captured("name");
        t.mCateogry = ARRAY;
        t.mFilePath = filePath;
        t.mLineNum = startingLine + text.left(m.capturedStart()).count('\n');
        t.mArrayType = m.captured("type");

        QRegularExpressionMatchIterator unconstrainedRangeMatches = unconstrainedRegex.globalMatch(m.captured("dims"));
        QRegularExpressionMatchIterator constrainedRangeMatches = constrainedRegex.globalMatch(m.captured("dims"));

        bool umValid = false;
        bool cmValid = false;
        QRegularExpressionMatch um;
        QRegularExpressionMatch cm;

        while (unconstrainedRangeMatches.hasNext() || constrainedRangeMatches.hasNext() || umValid || cmValid)
        {
            ArrayRange r;

            if (!umValid && unconstrainedRangeMatches.hasNext())
            {
                um = unconstrainedRangeMatches.next();
                umValid = true;
            }

            if (!cmValid && constrainedRangeMatches.hasNext())
            {
                cm = constrainedRangeMatches.next();
                cmValid = true;
            }

            if ((umValid && !cmValid) || ((umValid && cmValid) && (um.capturedStart() < cm.capturedStart())))
            {
                r.unconstrained = true;
                r.typeName = um.captured("name");
                t.mArrayDimensions.append(r);
                umValid = false;
            }
            else if (cmValid)
            {
                r.unconstrained = false;
                r.rangeLeft = cm.captured("left").toInt();
                r.rangeRight = cm.captured("right").toInt();
                if (cm.captured("dir") == "downto")
                    r.rangeDescending = true;
                else
                    r.rangeDescending = false;
                t.mArrayDimensions.append(r);
                cmValid = false;
            }
        }

        types.append(t);
    }

    return types;
}

bool HdlParserTypeDefinition::operator==(const HdlParserTypeDefinition &other)
{
    return ((other.mName == mName) && (other.mEnumValues == mEnumValues));
}

HdlParserTypeDefinition::TypeCategory HdlParserTypeDefinition::category() const
{
    return mCateogry;
}

void HdlParserTypeDefinition::setCateogry(TypeCategory c)
{
    mCateogry = c;
}

QString HdlParserTypeDefinition::name() const
{
    return mName;
}

void HdlParserTypeDefinition::setName(QString name)
{
    mName = name;
}

QStringList HdlParserTypeDefinition::enumValues() const
{
    return mEnumValues;
}

void HdlParserTypeDefinition::setEnumValues(QStringList ev)
{
    mEnumValues = ev;
}

void HdlParserTypeDefinition::addEnumValue(QString v)
{
    if (!mEnumValues.contains(v))
    {
        mEnumValues.append(v);
    }
}

void HdlParserTypeDefinition::removeEnumValue(QString v)
{
    mEnumValues.removeAll(v);
}

double HdlParserTypeDefinition::rangeLeft() const
{
    return mRangeLeft;
}

double HdlParserTypeDefinition::rangeRight() const
{
    return mRangeRight;
}

bool HdlParserTypeDefinition::rangeDescending() const
{
    return mRangeDescending;
}

QList<HdlParserTypeDefinition::ArrayRange> HdlParserTypeDefinition::arrayDimensions() const
{
    return mArrayDimensions;
}

QString HdlParserTypeDefinition::arrayType() const
{
    return mArrayType;
}

QString HdlParserTypeDefinition::filePath() const
{
    return mFilePath;
}

int HdlParserTypeDefinition::lineNum() const
{
    return mLineNum;
}
