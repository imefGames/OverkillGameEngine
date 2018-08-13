#include <stdafx.h>
#include <core\string.h>

namespace OK
{
    void Split(OK::char8* inputStringStart, OK::char8* inputStringEnd, Array<StringView>& outputStrings, OK::char8 splitChar)
    {
        OK::char8* currentStringStart{ inputStringStart };
        outputStrings.Clear();
        for (OK::char8* currentChar = inputStringStart; currentChar != inputStringEnd; ++currentChar)
        {
            if (*currentChar == splitChar)
            {
                outputStrings.Add(StringView{ currentStringStart , currentChar });
                currentStringStart = currentChar + 1;
            }
        }
        outputStrings.Add(StringView{ currentStringStart , inputStringEnd });
    }

    void Split(String& inputString, Array<StringView>& outputStrings, OK::char8 splitChar)
    {
        Split(inputString.begin(), inputString.end(), outputStrings, splitChar);
    }

    void Split(StringView& inputString, Array<StringView>& outputStrings, OK::char8 splitChar)
    {
        Split(inputString.begin(), inputString.end(), outputStrings, splitChar);
    }
}