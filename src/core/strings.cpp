#include "strings.hpp"
#include <iostream>

LocalizedString::LocalizedString(std::string s)
{
    SetValue(s);
}

void LocalizedString::SetValue(std::string s)
{
    mValue = s;
    mTrimmedValue = mValue;
    DetectIfLocalized();
}

void LocalizedString::DetectIfLocalized()
{
    mLocalized = mValue.length() > 0 && mValue[0] == '$';
    if (mLocalized && mValue.rfind("$Text::", 0) == 0)
        mTrimmedValue = mValue.substr(7);
}

std::string LocalizedString::ToString() const
{
    if (mValue.length() == 0)
        return "";//"<Empty>";

    if (mLocalized)
        return std::string(mValue + " | " + mTrimmedValue + " | Localized");

    return mValue;
}

std::ostream& operator<<(std::ostream& os, const LocalizedString& s)
{
    os << s.ToString();
    return os;
}