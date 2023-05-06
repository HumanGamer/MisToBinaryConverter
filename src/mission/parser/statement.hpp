#pragma once

#include <platform/types.h>

#include <string>
#include <vector>


namespace MissionParser
{
    enum class StatementKind : U32
    {
#define STATEMENT_KIND(name) name,
#include "StatementKinds.inc."
#undef STATEMENT_KIND
    };

    static const char* sStatementKindNames[] =
    {
#define STATEMENT_KIND(name) #name,
#include "StatementKinds.inc."
#undef STATEMENT_KIND
    };

    class Statement
    {
    public:
        std::string mName;
        std::vector<Statement> mParameters;
        StatementKind mKind{StatementKind::UNKNOWN};

        void debugPrint(size_t indent) const;
    };
    
}
