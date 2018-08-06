#include <stdafx.h>
#include <core\io\parsers\parserutils.h>

namespace OK
{
    namespace ParserUtils
    {
        EResult GetNextToken(const StringView& text, StringView& foundToken)
        {
            return EResult::Failure;
        }

        EResult ParseUntil(const StringView& text, StringView& foundToken, StringView& endToken, const OK::char8* endSymbols)
        {
            return EResult::Failure;
        }
    }
}