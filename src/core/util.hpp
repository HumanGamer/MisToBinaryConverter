#pragma once

#include <platform/types.h>
#include <string>
#include <map>
#include <crossguid/guid.hpp>

extern bool equalsIgnoreCase(const std::string& s1, const std::string& s2);
extern std::string formatTime(U32 milliseconds);
extern xg::Guid stringToGuid(const std::string& str);
extern std::string guidToString(const xg::Guid& guid);
extern std::string cleanPath(const std::string& str);
extern bool containsIgnoreCase(const std::vector<std::string>& list, const std::string& str);
extern std::string getFullPath(const std::string& path);
extern std::string getDirectory(const std::string& path);
extern std::string getRelativePath(const std::string& path, const std::string& relativeTo);
