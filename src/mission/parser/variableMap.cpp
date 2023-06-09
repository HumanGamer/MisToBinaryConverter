#include "variableMap.hpp"
#include <iostream>
#include <utility>

#define RETURN_IF_NOT_EXIST(retcode) \
    auto it = mVariables.find(name); \
    if (it == mVariables.end()) \
        return retcode
namespace MissionParser
{
    // -------------------------------------------------------------------------
    // Constructor/Destructor
    // -------------------------------------------------------------------------

    VariableMap::VariableMap() = default;

    VariableMap::VariableMap(CaseInsensitiveMap<std::string> variables)
    {
        setVariableMap(std::move(variables));
    }

    VariableMap::~VariableMap() = default;

    void VariableMap::setVariableMap(CaseInsensitiveMap<std::string> variables)
    {
        mVariables = std::move(variables);
    }

    // -------------------------------------------------------------------------

    bool VariableMap::containsVariable(const std::string& name)
    {
        RETURN_IF_NOT_EXIST(false);
        return true;
    }

    // -------------------------------------------------------------------------
    // Getters
    // -------------------------------------------------------------------------

    std::string VariableMap::getString(const std::string& name)
    {
        RETURN_IF_NOT_EXIST("");
        return it->second;
    }

    Point VariableMap::getPoint(const std::string& name)
    {
        RETURN_IF_NOT_EXIST(Point());

        Point p;
        sscanf_s(it->second.c_str(), "%f %f %f", &p.x, &p.y, &p.z);

        return p;
    }

    AngAxis VariableMap::getAngAxis(const std::string& name)
    {
        RETURN_IF_NOT_EXIST(AngAxis());

        AngAxis a;
        sscanf_s(it->second.c_str(), "%f %f %f %f", &a.x, &a.y, &a.z, &a.angle);

        return a;
    }

    Polyhedron VariableMap::getPolyhedron(const std::string &name)
    {
        RETURN_IF_NOT_EXIST(Polyhedron());

        Polyhedron p;
        sscanf_s(it->second.c_str(), "%f %f %f %f %f %f %f %f %f %f %f %f",
            &p.origin.x, &p.origin.y, &p.origin.z,
            &p.points[0].x, &p.points[0].y, &p.points[0].z,
            &p.points[1].x, &p.points[1].y, &p.points[1].z,
            &p.points[2].x, &p.points[2].y, &p.points[2].z);

        return p;
    }

    bool VariableMap::getBool(const std::string& name)
    {
        RETURN_IF_NOT_EXIST("");
        if (it->second == "true" || it->second == "1")
            return true;
        return false;
    }

    U32 VariableMap::getInt(const std::string& name)
    {
        RETURN_IF_NOT_EXIST(0);

        try {
            return std::stoi(it->second);
        } catch (std::exception &err)
        {
            std::cerr << "Failed to convert string to int: " << it->second << std::endl;
            return 0;
        }
    }
}
