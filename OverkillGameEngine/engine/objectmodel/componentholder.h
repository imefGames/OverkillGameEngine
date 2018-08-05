#pragma once

namespace OK
{
    using ComponentHolderID = OK::u64;
    using ComponentFactoryID = OK::u64;
    constexpr ComponentHolderID K_INVALID_COMPONENT_HOLDER = 0xFFFFFFFFFFFFFFFF;
    constexpr ComponentFactoryID K_INVALID_COMPONENT_FACTORY = 0xFFFFFFFFFFFFFFFF;

    class ComponentHolder
    {
    public:
        static ComponentHolderID GetNextComponentHolderID();
    };
}