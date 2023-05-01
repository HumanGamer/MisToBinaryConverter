#include "Util.hpp"
#include <algorithm>

bool equalsIgnoreCase(const std::string& s1, const std::string& s2)
{
    if (s1.length() != s2.length())
        return false;

    std::string s1_lower = s1;
    std::string s2_lower = s2;
    std::transform(s1_lower.begin(), s1_lower.end(), s1_lower.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    std::transform(s2_lower.begin(), s2_lower.end(), s2_lower.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    return s1_lower == s2_lower;
}

std::string formatTime(U32 milliseconds)
{
    F32 hundredths = floor((milliseconds % 1000) / 10.0f);
    F32 totalSeconds = floor(milliseconds / 1000.0f);
    F32 seconds = (U32)totalSeconds % 60;
    F32 minutes = (totalSeconds - seconds) / 60.0f;
    F32 secondsOne = (U32)seconds % 10;
    F32 secondsTen = (seconds - secondsOne) / 10.0f;
    F32 minutesOne = (U32)minutes % 10;
    F32 minutesTen = (minutes - minutesOne) / 10.0f;
    F32 hundredthsOne = (U32)hundredths % 10;
    F32 hundredthsTen = (hundredths - hundredthsOne) / 10.0f;

    return std::to_string((U32)minutesTen) + std::to_string((U32)minutesOne) + ":" +
           std::to_string((U32)secondsTen) + std::to_string((U32)secondsOne) + "." +
           std::to_string((U32)hundredthsTen) + std::to_string((U32)hundredthsOne);
}

xg::Guid stringToGuid(const std::string& str)
{
    const char* strC = str.c_str();
    xg::Guid result;

    if (strC[0] == '{' && strC[strlen(strC) - 1] == '}')
    {
        char s[256];
        strcpy_s(s, strC + 1);
        s[strlen(s) - 1] = '\0';
        result = xg::Guid(s);
    } else {
        result = xg::Guid(strC);
    }

    return result;
}