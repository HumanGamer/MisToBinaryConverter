#include "objectDefinition.hpp"
#include "variableMap.hpp"
#include <iostream>

namespace MissionParser
{
    void ObjectDefinition::debugPrint(size_t indent) const
    {
        std::string indent_str(indent, '\t');
        std::cout << indent_str << "OBJECT_DECLARATION " << mClassName << " " << mName;
        if (mStatements.empty() && mChildren.empty())
        {
            std::cout << "()" << std::endl;
        } else
        {
            std::cout << std::endl;
            std::cout << indent_str << "(" << std::endl;
            for (const Statement& statement: mStatements)
            {
                statement.debugPrint(indent + 1);
            }
            for (const ObjectDefinition& obj: mChildren)
            {
                obj.debugPrint(indent + 1);
            }
            std::cout << indent_str << ")" << std::endl;
        }
    }

    bool ObjectDefinition::getVariables(CaseInsensitiveMap<std::string>* variables) const
    {
        for (auto& statement : mStatements)
        {
            std::string name = statement.mName;
            if (statement.mParameters.size() != 1)
            {
                std::string s = "Internal error, the variable has more than one value";
                std::cerr << s << std::endl;
                //throw std::runtime_error(s);
                return false;
            }
            std::string value = statement.mParameters[0].mName;
            (*variables)[name] = value;
        }
        return true;
    }

    bool ObjectDefinition::getVariableMap(MissionParser::VariableMap *variables) const
    {
        CaseInsensitiveMap<std::string> vars;
        if (!getVariables(&vars))
            return false;

        variables->setVariableMap(vars);

        return true;
    }
}
