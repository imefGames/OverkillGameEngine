#pragma once

#include <core\containers\basestring.h>
#include <core\containers\basestringview.h>

namespace OK
{
    using String = BaseString<OK::char8>;
    using StringView = BaseStringView<OK::char8>;

    void Split(OK::char8* inputStringStart, OK::char8* inputStringEnd, Array<StringView>& outputStrings, OK::char8 splitChar);
    void Split(String& inputString, Array<StringView>& outputStrings, OK::char8 splitChar);
    void Split(StringView& inputString, Array<StringView>& outputStrings, OK::char8 splitChar);

    template<typename T>
    inline auto ConvertFromString(const OK::char8* string, OK::u32 length) -> decltype(auto)
    {
        return T{};
    }

    template<>
    inline auto ConvertFromString<OK::u32>(const OK::char8* string, OK::u32 length) -> decltype(auto)
    {
        String str;
        str.Resize(length + 1);
        OK::MemCopy(string, str.begin(), length);
        str[length] = '\0';
        return static_cast<OK::u32>(std::atoi(str.begin()));
    }

    template<>
    inline auto ConvertFromString<OK::f32>(const OK::char8* string, OK::u32 length) -> decltype(auto)
    {
        String str;
        str.Resize(length + 1);
        OK::MemCopy(string, str.begin(), length);
        str[length] = '\0';
        return static_cast<OK::f32>(std::atof(str.begin()));
    }

    template<>
    inline auto ConvertFromString<OK::Bool>(const OK::char8* string, OK::u32 length) -> decltype(auto)
    {
        OK::Bool isTrue{ OK::MemEqual(string, "true", length) };
        OK::Bool isFalse{ OK::MemEqual(string, "false", length) };
        okAssert(isTrue || isFalse, "Invalid boolean value.");

        return isTrue;
    }
}