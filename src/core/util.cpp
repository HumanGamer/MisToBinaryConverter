#include "util.hpp"
#include <algorithm>
#include <filesystem>

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

std::string guidToString(const xg::Guid& guid)
{
    if (guid.isValid())
    {
        std::string str = guid.str();
        std::transform(str.begin(), str.end(), str.begin(), ::toupper);
        return "{" + str + "}";
    } else
        return "{INVALID_GUID}";
}

std::string cleanPath(const std::string& str)
{
    std::string result = str;

    // replace \ with /
    std::replace(result.begin(), result.end(), '\\', '/');

    // remove ./ from the path if it starts with it
    if (result.length() > 2 && result[0] == '.' && result[1] == '/')
        result = result.substr(2);

    // remove ~/ from the path if it starts with it
    if (result.length() > 2 && result[0] == '~' && result[1] == '/')
        result = result.substr(2);

    // remove marble/ from the path if it starts with it
    if (result.length() > 8 && result.substr(0, 8) == "marble/")
        result = result.substr(8);

    // remove data/missions/ from the path if it starts with it
    if (result.length() > 15 && result.substr(0, 14) == "data/missions/")
        result = result.substr(14);

    return result;
}

bool containsIgnoreCase(const std::vector<std::string>& list, const std::string& str)
{
    return std::any_of(list.begin(), list.end(), [str](const std::string& s) { return equalsIgnoreCase(s, str); });

//    for (const std::string& s : list)
//    {
//        if (equalsIgnoreCase(s, str))
//            return true;
//    }
//
//    return false;
}

std::string getFullPath(const std::string& path)
{
    std::filesystem::path p = path;

    return std::filesystem::absolute(p).string();
}

std::string getDirectory(const std::string& path)
{
    std::filesystem::path p = path;

    return std::filesystem::absolute(p).parent_path().string();
}

std::string getRelativePath(const std::string& path, const std::string& relativeTo)
{
    std::filesystem::path p = path;
    std::filesystem::path r = relativeTo;

    return std::filesystem::relative(p, r).string();
}
