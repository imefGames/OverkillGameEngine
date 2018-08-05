#pragma once

namespace OK
{
    using ComponentHolderID = OK::u64;

    constexpr ComponentHolderID K_INVALID_COMPONENT_HOLDER = 0xFFFFFFFFFFFFFFFF;

    namespace ComponentHolderHelper
    {
        ComponentHolderID GetNextComponentHolderID();
    }
}