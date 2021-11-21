#ifndef SEMANTICVERSION_H
#define SEMANTICVERSION_H


class SemanticVersion
{
public:
    SemanticVersion(int major = 0, int minor = 0, int patch = 0);

    int major() const;
    void setMajor(int major);

    int minor() const;
    void setMinor(int minor);

    int patch() const;
    void setPatch(int patch);

    SemanticVersion nextMajor() const;
    SemanticVersion nextMinor() const;
    SemanticVersion nextPatch() const;

    bool operator==(const SemanticVersion& other) const;
    bool operator!=(const SemanticVersion& other) const;
    bool operator<(const SemanticVersion& other) const;
    bool operator<=(const SemanticVersion& other) const;
    bool operator>(const SemanticVersion& other) const;
    bool operator>=(const SemanticVersion& other) const;

private:
    int mMajorVersion;
    int mMinorVersion;
    int mPatchVersion;

};

#endif // SEMANTICVERSION_H
