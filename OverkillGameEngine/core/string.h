#pragma once

#include <stdafx.h>
#include <core\containers\basestring.h>
#include <core\containers\basestringview.h>

namespace OK
{
    using String = BaseString<OK::char8>;
    using StringView = BaseStringView<OK::char8>;

    template<typename T>
    inline auto ConvertFromString(const OK::char8* string, OK::u32 length) -> decltype(auto)
    {
        return T{};
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
}