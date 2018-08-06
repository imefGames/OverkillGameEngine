#pragma once

namespace OK
{
    namespace ParserUtils
    {
        EResult GetNextToken(const StringView& text, StringView& foundToken);
        EResult ParseUntil(const StringView& text, StringView& foundToken, StringView& endToken, const OK::char8* endSymbols);
    }
}