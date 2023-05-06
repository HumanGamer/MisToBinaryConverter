#include "Statement.hpp"
#include <iostream>

namespace MissionParser
{
    void Statement::debugPrint(size_t indent) const
    {
        std::cout << std::string(indent, '\t') << sStatementKindNames[U32(mKind)] << " ";
        std::cout << mName << std::endl;
        if (!mParameters.empty())
        {
            std::cout << std::string(indent, '\t') << "(" << std::endl;
            for (Statement statement: mParameters)
            {
                statement.debugPrint(indent + 1);
            }
            std::cout << std::string(indent, '\t') << ")" << std::endl;
        }
    }
}