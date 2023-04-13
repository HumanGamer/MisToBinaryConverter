#pragma once

#include <platform/types.h>
#include <CaseInsensitiveMap.hpp>
#include "Statement.hpp"
#include <string>
#include <vector>
#include <map>

namespace MissionParser
{
    class VariableMap;

    class ObjectDefinition
    {
    public:
        std::string mName;
        std::string mClassName;
        std::vector<Statement> mStatements;
        std::vector<ObjectDefinition> mChildren;

        bool getVariables(CaseInsensitiveMap<std::string>* variables) const;
        bool getVariableMap(MissionParser::VariableMap* variables) const;

        void debugPrint(size_t indent) const;
    };
}