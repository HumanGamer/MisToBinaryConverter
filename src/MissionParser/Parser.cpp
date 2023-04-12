#include "Parser.hpp"
#include <stdexcept>
#include <iostream>

namespace MissionParser
{
    void Parser::parse(std::vector<Token> &tokens)
    {
        mEndToken = tokens.end();
        mCurrentToken = tokens.begin();

        while (mCurrentToken != mEndToken)
        {
            std::optional<ObjectDefinition> obj = expectObject();
            if (obj.has_value())
            {
                mObjects[obj->mName] = obj.value();
            } else {
                std::cerr << "Unknown identifier: " << mCurrentToken->mText << std::endl;
                mCurrentToken++;
            }
        }
    }

    std::optional<ObjectDefinition> Parser::expectObject()
    {
        std::vector<Token>::iterator parseStart = mCurrentToken;
        std::optional<Token> identifier = expectIdentifier();
        if (identifier.has_value())
        {
            if (identifier->mText != "new")
            {
                //throw std::runtime_error("Expected 'new' but got: " + identifier->mText);
                mCurrentToken = parseStart;
                return std::nullopt;
            }

            std::optional<Token> objectClass = expectIdentifier();
            if (!objectClass.has_value())
            {
                throw std::runtime_error("Expected object class but got: " + mCurrentToken->mText);
                mCurrentToken = parseStart;
                return std::nullopt;
            }

            if (!expectOperator("(").has_value())
            {
                throw std::runtime_error("Expected '(' but got: " + mCurrentToken->mText);
                mCurrentToken = parseStart;
                return std::nullopt;
            }

            std::optional<Token> objectName = expectIdentifier();

            if (!expectOperator(")").has_value())
            {
                throw std::runtime_error("Expected ')' but got: " + mCurrentToken->mText);
                mCurrentToken = parseStart;
                return std::nullopt;
            }

            ObjectDefinition obj;
            if (objectName.has_value())
                obj.mName = objectName.value().mText;
            else
                obj.mName = "";
            obj.mClassName = objectClass.value().mText;

            std::optional<std::vector<Statement>> statements = parseObjectBody(obj);
            if (!statements.has_value())
            {
                mCurrentToken = parseStart;
                return std::nullopt;
            }

            obj.mStatements.insert(obj.mStatements.begin(), statements->begin(), statements->end());

            return obj;
        }

        mCurrentToken = parseStart;
        return std::nullopt;
    }

    std::optional<std::vector<Statement>> Parser::parseObjectBody(ObjectDefinition &def)
    {
        if (!expectOperator("{").has_value())
        {
            throw std::runtime_error("Expected '{' but got: " + mCurrentToken->mText);
            return std::nullopt;
        }

        std::vector<Statement> statements;

        while (!expectOperator("}").has_value())
        {
            std::optional<Statement> statement = expectStatement();
            if (statement.has_value())
                statements.push_back(statement.value());

            std::optional<Token> semicolon = expectOperator(";");

            if (!semicolon.has_value())
            {
                std::optional<ObjectDefinition> obj = expectObject();

                if (obj.has_value())
                {
                    def.mChildren.push_back(obj.value());
                } else {
                    size_t lineNo = (mCurrentToken != mEndToken ? mCurrentToken->mLineNumber : 999999);
                    std::string s = std::string("Expected ';' at end of statement in line ") + std::to_string(lineNo) + ".";
                    std::cerr << s << std::endl;
                    throw std::runtime_error(s);
                    return std::nullopt;
                }
            }
        }

        if (!expectOperator(";").has_value())
        {
            throw std::runtime_error("Expected ';' but got: " + mCurrentToken->mText);
            return std::nullopt;
        }

        return statements;
    }

    std::optional<Token> Parser::expectIdentifier(const std::string &name)
    {
        if (mCurrentToken == mEndToken)
            return std::nullopt;

        if (mCurrentToken->mType != TokenType::IDENTIFIER)
            return std::nullopt;

        if (!name.empty() && mCurrentToken->mText != name)
            return std::nullopt;

        Token returnToken = *mCurrentToken;
        mCurrentToken++;
        return returnToken;
    }

    std::optional<Token> Parser::expectOperator(const std::string &name)
    {
        if (mCurrentToken == mEndToken)
            return std::nullopt;

        if (mCurrentToken->mType != TokenType::OPERATOR)
            return std::nullopt;

        if (!name.empty() && mCurrentToken->mText != name)
            return std::nullopt;

        Token returnToken = *mCurrentToken;
        mCurrentToken++;
        return returnToken;
    }

    std::optional<Statement> Parser::expectOneValue()
    {
        std::optional<Statement> result;
        auto savedToken = mCurrentToken;

        if (mCurrentToken != mEndToken && mCurrentToken->mType == FLOAT_LITERAL)
        {
            Statement floatLiteralStatement;
            floatLiteralStatement.mKind = StatementKind::LITERAL;
            floatLiteralStatement.mName = mCurrentToken->mText;
            result = floatLiteralStatement;
            mCurrentToken++;
        } else if (mCurrentToken != mEndToken && mCurrentToken->mType == INTEGER_LITERAL)
        {
            Statement integerLiteralStatement;
            integerLiteralStatement.mKind = StatementKind::LITERAL;
            integerLiteralStatement.mName = mCurrentToken->mText;
            result = integerLiteralStatement;
            mCurrentToken++;
        } else if (mCurrentToken != mEndToken && mCurrentToken->mType == STRING_LITERAL)
        {
            Statement stringLiteralStatement;
            stringLiteralStatement.mKind = StatementKind::LITERAL;
            stringLiteralStatement.mName = mCurrentToken->mText;
            result = stringLiteralStatement;
            mCurrentToken++;
        } else if (auto variableName = expectIdentifier())
        {
            if (expectOperator("("))
                mCurrentToken = savedToken;
            else
            {
                Statement variableNameStatement;
                variableNameStatement.mKind = StatementKind::VARIABLE_NAME;
                variableNameStatement.mName = variableName->mText;
                result = variableNameStatement;
            }
        }

        if (!result.has_value())
        {
            throw new std::runtime_error("Expected value but got: " + mCurrentToken->mText);
            mCurrentToken = savedToken;
            return std::nullopt;
        }

        return result;
    }

    std::optional<Statement> Parser::expectStatement()
    {
        std::optional<Statement> statement = expectVariableDeclaration();
        if (statement.has_value())
            return statement;

        return std::nullopt;
    }

    std::optional<Statement> Parser::expectVariableDeclaration()
    {
        std::vector<Token>::iterator startToken = mCurrentToken;

        std::optional<Token> name = expectIdentifier();
        if (!name.has_value())
        {
            mCurrentToken = startToken;
            return std::nullopt;
        }

        std::optional<Token> equals = expectOperator("=");
        if (!equals.has_value())
        {
            mCurrentToken = startToken;
            return std::nullopt;
        }

        std::optional<Statement> value = expectOneValue();
        if (!value.has_value())
        {
            mCurrentToken = startToken;
            return std::nullopt;
        }

        Statement statement;
        statement.mKind = StatementKind::VARIABLE_DECLARATION;
        statement.mName = name->mText;
        statement.mParameters.push_back(value.value());

        return statement;
    }

    void Parser::debugPrint() const
    {
        for (auto obj : mObjects)
        {
            obj.second.debugPrint(0);
        }
    }
}
