#include <stdafx.h>
#include <core\io\parsers\parserutils.h>

#include <cctype>

namespace OK
{
    namespace ParserUtils
    {
        EResult GetNextToken(const StringView& text, StringView& foundToken)
        {
            EResult parseResult{ EResult::Success };
            EParserTokenType tokenType{ EParserTokenType::Unknown };
            StringView::iterator lineIterator{ text.begin() };
            StringView::iterator beginIterator{ text.begin() };
            StringView::iterator endIterator{ text.end() };
            StringView::iterator foundIterator{ text.end() };

            if (lineIterator == endIterator)
            {
                parseResult = EResult::Failure;
            }

            while (lineIterator != endIterator && foundIterator == endIterator)
            {
                bool hasFoundToken{ false };
                char currentChar = *lineIterator;
                if (!std::isspace(currentChar) && tokenType == EParserTokenType::Unknown)
                {
                    beginIterator = lineIterator;
                }
                if (tokenType != EParserTokenType::String && tokenType != EParserTokenType::Unknown && std::isspace(currentChar))
                {
                    foundIterator = lineIterator;
                }
                else
                {
                    switch (tokenType)
                    {
                        case EParserTokenType::Operator:
                        {
                            if (std::isdigit(currentChar))
                            {
                                //HACK to handle negative numbers
                                tokenType = EParserTokenType::Number;
                            }
                            else if (!std::ispunct(currentChar))
                            {
                                //TODO: ReportError("Invalid character in symbol (%x). Expected an operator character.", currentChar);
                                parseResult = EResult::Failure;
                                hasFoundToken = true;
                            }
                            break;
                        }

                        case EParserTokenType::String:
                        {
                            if (currentChar == '"')
                            {
                                hasFoundToken = true;
                            }
                            break;
                        }

                        case EParserTokenType::Number:
                        {
                            if (!std::isdigit(currentChar) && !std::ispunct(currentChar))
                            {
                                //TODO: ReportError("Invalid character in symbol (%x). Expected a digit.", currentChar);
                                parseResult = EResult::Failure;
                                hasFoundToken = true;
                            }
                            break;
                        }

                        case EParserTokenType::Word:
                        {
                            if (!std::isalnum(currentChar))
                            {
                                //TODO: ReportError("Invalid character in symbol (%x). Expected an alphanumeric character.", currentChar);
                                parseResult = EResult::Failure;
                                hasFoundToken = true;
                            }
                            break;
                        }

                        default:
                        {
                            if (std::isalpha(currentChar))
                            {
                                tokenType = EParserTokenType::Word;
                            }
                            else if (std::isdigit(currentChar))
                            {
                                tokenType = EParserTokenType::Number;
                            }
                            else if (currentChar == '"')
                            {
                                tokenType = EParserTokenType::String;
                            }
                            else if (std::ispunct(currentChar))
                            {
                                tokenType = EParserTokenType::Operator;
                            }
                            else if (!std::isspace(currentChar))
                            {
                                //TODO: ReportError("Can't start symbol with char %x.", currentChar);
                                parseResult = EResult::Failure;
                                hasFoundToken = true;
                            }
                            break;
                        }
                    }
                }
                ++lineIterator;
                if (hasFoundToken)
                {
                    foundIterator = lineIterator;
                }
            }
            foundToken = StringView(beginIterator, foundIterator);
            return parseResult;
        }

        EResult ParseUntilEndOfScope(const StringView& text, StringView& foundToken, StringView& endToken)
        {
            OK::u32 scopeDepth{ 0 };
            EResult parseResult{ EResult::Failure };
            StringView nextToken{ text.begin(), text.begin() };
            StringView::iterator currentBegin{ text.begin() };
            StringView::iterator currentEnd{ text.end() };
            while (GetNextToken(StringView{ nextToken.end(), text.end() }, nextToken) == EResult::Success && parseResult != EResult::Success)
            {
                if (nextToken == "}" || nextToken == "]" || nextToken == ",")
                {
                    if (scopeDepth == 0)
                    {
                        endToken = nextToken;
                        foundToken = StringView{ currentBegin, currentEnd };
                        parseResult = EResult::Success;
                    }
                    else if (nextToken == "}" || nextToken == "]")
                    {
                        --scopeDepth;
                    }
                }
                else if (nextToken == "{" || nextToken == "[")
                {
                    ++scopeDepth;
                }
                currentEnd = nextToken.end();
            }
            return parseResult;
        }
    }
}