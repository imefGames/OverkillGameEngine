#pragma once

#include <stdafx.h>
#include <core\containers\basestring.h>
#include <core\containers\basestringview.h>

namespace OK
{
    using String = BaseString<OK::char8>;
    using StringView = BaseStringView<OK::char8>;
}