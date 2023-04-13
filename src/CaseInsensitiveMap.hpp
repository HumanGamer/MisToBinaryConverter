#pragma once

#include <string>
#include <map>

namespace detail
{
// https://stackoverflow.com/questions/1801892/how-can-i-make-the-mapfind-operation-case-insensitive
    struct CaseInsensitiveComparator
    {
        // case-independent (ci) compare_less binary function
        struct nocase_compare
        {
            bool operator()(const unsigned char &c1, const unsigned char &c2) const
            {
                return tolower(c1) < tolower(c2);
            }
        };

        bool operator()(const std::string &s1, const std::string &s2) const
        {
            return std::lexicographical_compare
                (s1.begin(), s1.end(),   // source range
                 s2.begin(), s2.end(),   // dest range
                 nocase_compare());  // comparison
        }
    };
}

template <typename T>
using CaseInsensitiveMap = std::map<std::string, T, detail::CaseInsensitiveComparator>;
