#pragma once

#include <platform/types.h>
#include <string>

class LocalizedString
{
public:
    LocalizedString(std::string s = "");

    std::string GetValue() const { return mValue; }
    std::string GetTrimmedValue() const { return mTrimmedValue; }
    bool IsLocalized() const { return mLocalized; }

    void SetValue(std::string s);

    friend std::ostream& operator<<(std::ostream& os, const LocalizedString& s);

    std::string ToString() const;

private:
    void DetectIfLocalized();

    std::string mValue;
    std::string mTrimmedValue;
    bool mLocalized;
};
