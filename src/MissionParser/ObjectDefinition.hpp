#pragma once

#include <platform/types.h>
#include "Statement.hpp"
#include <string>
#include <vector>

namespace MissionParser
{
    class ObjectDefinition
    {
    public:
        std::string mName;
        std::string mClassName;
        std::vector<Statement> mStatements;
        std::vector<ObjectDefinition> mChildren;

        void debugPrint(size_t indent) const;
    };
}