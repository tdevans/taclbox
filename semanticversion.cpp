#include "semanticversion.h"
#include <QDebug>

SemanticVersion::SemanticVersion(int major, int minor, int patch)
    :mMajorVersion(major), mMinorVersion(minor), mPatchVersion(patch)
{

}

int SemanticVersion::major() const
{
    return mMajorVersion;
}

void SemanticVersion::setMajor(int major)
{
    if (major >= 0)
    {
        mMajorVersion = major;
    }
    else
    {
        qWarning() << QString("Attempted to set major version to %1").arg(major);
    }
}

int SemanticVersion::minor() const
{
    return mMinorVersion;
}

void SemanticVersion::setMinor(int minor)
{
    if (minor >= 0)
    {
        mMinorVersion = minor;
    }
    else
    {
        qWarning() << QString("Attempted to set minor version to %1").arg(minor);
    }
}

int SemanticVersion::patch() const
{
    return mPatchVersion;
}

void SemanticVersion::setPatch(int patch)
{
    if (patch >= 0)
    {
        mPatchVersion = patch;
    }
    else
    {
        qWarning() << QString("Attempted to set patch version to %1").arg(patch);
    }
}

SemanticVersion SemanticVersion::nextMajor() const
{
    SemanticVersion next(mMajorVersion + 1);
    return next;
}

SemanticVersion SemanticVersion::nextMinor() const
{
    SemanticVersion next(mMajorVersion, mMinorVersion + 1);
    return next;
}

SemanticVersion SemanticVersion::nextPatch() const
{
    SemanticVersion next(mMajorVersion, mMinorVersion, mPatchVersion + 1);
    return next;
}

bool SemanticVersion::operator==(const SemanticVersion &other) const
{
    if ((mMajorVersion == other.mMajorVersion) && (mMinorVersion == other.mMinorVersion) && (mPatchVersion == other.mPatchVersion))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool SemanticVersion::operator!=(const SemanticVersion &other) const
{
    return !operator==(other);
}

bool SemanticVersion::operator<(const SemanticVersion &other) const
{
    if (mMajorVersion < other.mMajorVersion)
    {
        return true;
    }
    else if (mMajorVersion > other.mMajorVersion)
    {
        return false;
    }
    else
    {
        if (mMinorVersion < other.mMinorVersion)
        {
            return true;
        }
        else if (mMinorVersion > other.mMinorVersion)
        {
            return false;
        }
        else
        {
            if (mPatchVersion < other.mPatchVersion)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}

bool SemanticVersion::operator<=(const SemanticVersion &other) const
{
    return (operator<(other) || operator==(other));
}

bool SemanticVersion::operator>(const SemanticVersion &other) const
{
    return !operator<=(other);
}

bool SemanticVersion::operator>=(const SemanticVersion &other) const
{
    return !operator<(other);
}
