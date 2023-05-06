#pragma once

#include <platform/types.h>
#include <string>
#include <map>
#include <crossguid/guid.hpp>

extern bool equalsIgnoreCase(const std::string& s1, const std::string& s2);
extern std::string formatTime(U32 milliseconds);
extern xg::Guid stringToGuid(const std::string& str);
extern std::string guidToString(const xg::Guid& guid);
