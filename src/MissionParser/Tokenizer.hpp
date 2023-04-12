#pragma once

#include <platform/types.h>
#include <vector>
#include <string>

namespace MissionParser
{
    enum TokenType
    {
#define TOKEN_TYPE(name) name,
#include "TokenTypes.inc"
#undef TOKEN_TYPE
    };

    static const char* sTokenTypeNames[] =
    {
#define TOKEN_TYPE(name) #name,
#include "TokenTypes.inc"
#undef TOKEN_TYPE
    };

    class Token
    {
    public:
        enum TokenType mType{WHITESPACE};
        std::string mText;
        size_t mLineNumber{0};

        void debugPrint() const;
    };

    class Tokenizer
    {
    public:
        std::vector<Token> parse(const std::string &input);

    private:
        void endToken(Token &token, std::vector<Token> &tokens);
    };
}
