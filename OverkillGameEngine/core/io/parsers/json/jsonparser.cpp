#include <stdafx.h>
#include <core\io\parsers\json\jsonparser.h>
#include <core\io\parsers\json\jsonnode.h>

#include <cctype>

namespace OK
{
    void JSONParser::Parse(String::const_iterator searchStart, String::const_iterator searchEnd, JSONNode& result)
    {
        ParseInternal(searchStart, searchEnd, result, nullptr);
        okAssert(searchStart == searchEnd, "Premature EOF.");
    }

    void JSONParser::ParseInternal(String::const_iterator& searchStart, String::const_iterator searchEnd, JSONNode& result, const JSONNode* parent)
    {
        bool expectColon{ false };
        StringView currentToken;
        while (searchStart != searchEnd)
        {
            FindNextToken(searchStart, searchEnd, searchStart, currentToken);
            if (currentToken == ":")
            {
                okAssert(expectColon, "Unexpected symbol: ':'.");
                okAssert(parent == nullptr || parent->m_NodeType != JSONNode::ENodeType::Array, "Can't use ':' is parent node is an array.");
                expectColon = false;
            }
            else
            {
                okAssert(!expectColon, "Expecting symbol ':'.");
                if (currentToken == "{")
                {
                    result.m_NodeType = JSONNode::ENodeType::Object;
                    JSONNode& newNode{ result.m_SubNodes.Grow() };
                    ParseInternal(searchStart, searchEnd, newNode, &result);
                }
                else if (currentToken == "[")
                {
                    result.m_NodeType = JSONNode::ENodeType::Array;
                    JSONNode& newNode{ result.m_SubNodes.Grow() };
                    ParseInternal(searchStart, searchEnd, newNode, &result);
                }
                else if (currentToken == "}")
                {
                    okAssert(result.m_NodeType == JSONNode::ENodeType::Object, "Symbol ']' should be used only at the end of object.");
                    break;
                }
                else if (currentToken == "]")
                {
                    okAssert(result.m_NodeType == JSONNode::ENodeType::Array, "Symbol ']' should be used only at the end of arrays.");
                    break;
                }
                else if (currentToken == ",")
                {
                    okAssert(result.m_NodeType == JSONNode::ENodeType::Object || result.m_NodeType == JSONNode::ENodeType::Array, "Unexpected symbol: ','.");
                    JSONNode& newNode{ result.m_SubNodes.Grow() };
                    ParseInternal(searchStart, searchEnd, newNode, &result);
                }
                else if (currentToken == ":")
                {
                    okAssert(expectColon, "Unexpected symbol: ':'.");
                    okAssert(parent == nullptr || parent->m_NodeType != JSONNode::ENodeType::Array, "Can't use ':' is parent node is an array.");
                    expectColon = false;
                }
                else
                {
                    okAssert(result.m_NodeType == JSONNode::ENodeType::Undefined, "Can't use such a token in defined nodes.");
                    if ((parent == nullptr || parent->m_NodeType != JSONNode::ENodeType::Array) && result.m_Name.IsEmpty())
                    {
                        result.m_Name = currentToken;
                        expectColon = true;
                    }
                    else
                    {
                        result.m_Value = currentToken;
                        result.m_NodeType = JSONNode::ENodeType::Leaf;
                        break;
                    }
                }
            }
        }
    }

    void JSONParser::FindNextToken(String::const_iterator searchStart, String::const_iterator searchEnd, String::const_iterator& nextSearchStart, StringView& foundToken)
    {
        enum class ETokenType
        {
            Unknown,
            Number,
            Word
        };

        ETokenType tokenType = ETokenType::Unknown;
        bool hasFoundToken{ false };
        SkipSpaces(searchStart, searchEnd);
        String::const_iterator startToken = searchStart;
        String::const_iterator endToken = searchEnd;
        while (searchStart != searchEnd && !hasFoundToken)
        {
            char currentChar = *searchStart;
            if (std::isspace(currentChar))
            {
                endToken = searchStart;
                hasFoundToken = true;
            }
            else
            {
                switch (tokenType)
                {
                case ETokenType::Number:
                {
                    if (!std::isdigit(currentChar) && currentChar != '.')
                    {
                        hasFoundToken = true;
                        endToken = searchStart--;
                    }
                    break;
                }

                case ETokenType::Word:
                {
                    if (!std::isalnum(currentChar))
                    {
                        hasFoundToken = true;
                        endToken = searchStart--;
                    }
                    break;
                }

                default:
                {
                    if (std::isalpha(currentChar))
                    {
                        tokenType = ETokenType::Word;
                    }
                    else if (std::isdigit(currentChar) || currentChar == '-' || currentChar == '.')
                    {
                        tokenType = ETokenType::Number;
                    }
                    else if (currentChar == '"')
                    {
                        startToken = ++searchStart;
                        SkipUntil(searchStart, searchEnd, '"');
                        endToken = searchStart;
                        hasFoundToken = true;
                    }
                    else if (std::ispunct(currentChar))
                    {
                        hasFoundToken = true;
                        endToken = searchStart + 1;
                    }
                    else
                    {
                        okAssert(false, "Invalide symbol.");
                    }
                    break;
                }
                }
            }

            ++searchStart;
        }
        nextSearchStart = searchStart;
        //TODO: remove const cast!!!!
        foundToken = StringView{ const_cast<OK::char8*>(startToken) , const_cast<OK::char8*>(endToken) };
    }

    void JSONParser::SkipSpaces(String::const_iterator& searchStart, String::const_iterator searchEnd)
    {
        while (std::isspace(*searchStart)  && searchStart != searchEnd)
        {
            ++searchStart;
        }
    }

    void JSONParser::SkipUntil(String::const_iterator& searchStart, String::const_iterator searchEnd, char endChar)
    {
        while (*searchStart != endChar && searchStart != searchEnd)
        {
            ++searchStart;
        }
    }
}