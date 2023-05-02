#pragma once

#include <platform/types.h>
#include <core/CaseInsensitiveMap.hpp>
#include <string>
#include <map>
#include "ObjectDefinition.hpp"

namespace MissionParser
{

    class VariableMap
    {
    public:
        VariableMap();
        explicit VariableMap(CaseInsensitiveMap<std::string> variables);
        virtual ~VariableMap();

        void setVariableMap(CaseInsensitiveMap<std::string> variables);

        bool containsVariable(const std::string& name);

        std::string getString(const std::string& name);
        Point getPoint(const std::string& name);
        AngAxis getAngAxis(const std::string& name);
        Polyhedron getPolyhedron(const std::string& name);
        bool getBool(const std::string& name);
        U32 getInt(const std::string& name);

    private:
        CaseInsensitiveMap<std::string> mVariables;
    };
}
