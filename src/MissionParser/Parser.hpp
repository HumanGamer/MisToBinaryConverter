#pragma once

#include <platform/types.h>
#include "Tokenizer.hpp"
#include "Statement.hpp"
#include "ObjectDefinition.hpp"
#include <optional>
#include <string>
#include <map>
#include <vector>

namespace MissionParser
{
    class Parser
    {
    public:
        void parse(std::vector<Token> &tokens);

        void debugPrint() const;

        std::vector<ObjectDefinition> &getObjects() { return mObjects; }

    private:
        std::vector<Token>::iterator mCurrentToken;
        std::vector<Token>::iterator mEndToken;

        std::vector<ObjectDefinition> mObjects;

        std::optional<ObjectDefinition> expectObject();
        std::optional<std::vector<Statement>> parseObjectBody(ObjectDefinition &def);

        // Empty string means many any identifier
        std::optional<Token> expectIdentifier(const std::string &name = std::string());

        // Empty string means many any identifier
        std::optional<Token> expectOperator(const std::string &name = std::string());

        std::optional<Statement> expectOneValue();

        std::optional<Statement> expectStatement();

        std::optional<Statement> expectVariableDeclaration();
    };
}