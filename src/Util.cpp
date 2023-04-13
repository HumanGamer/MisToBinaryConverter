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