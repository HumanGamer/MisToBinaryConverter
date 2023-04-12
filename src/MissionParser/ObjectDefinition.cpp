#include "ObjectDefinition.hpp"
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
            for (Statement statement: mStatements)
            {
                statement.debugPrint(indent + 1);
            }
            for (ObjectDefinition obj: mChildren)
            {
                obj.debugPrint(indent + 1);
            }
            std::cout << indent_str << ")" << std::endl;
        }
    }
}