#pragma once

namespace OK
{
    namespace ParserUtils
    {
        enum class EParserTokenType
        {
            Unknown,
            Operator,
            String,
            Number,
            Word
        };

        EResult GetNextToken(const StringView& text, StringView& foundToken);
        EResult ParseUntilEndOfScope(const StringView& text, StringView& foundToken, StringView& endToken);
    }
}