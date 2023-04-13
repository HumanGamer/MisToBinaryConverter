#pragma once

#include <platform/types.h>
#include <string>
#include <map>
#include "ObjectDefinition.hpp"

namespace MissionParser
{
    class VariableMap
    {
    public:
        VariableMap();
        explicit VariableMap(std::map<std::string, std::string> variables);
        virtual ~VariableMap();

        void setVariableMap(std::map<std::string, std::string> variables);

        bool containsVariable(const std::string& name);

        std::string getString(const std::string& name);
        Point getPoint(const std::string& name);
        AngAxis getAngAxis(const std::string& name);
        bool getBool(const std::string& name);
        U32 getInt(const std::string& name);

    private:
        std::map<std::string, std::string> mVariables;
    };
}
