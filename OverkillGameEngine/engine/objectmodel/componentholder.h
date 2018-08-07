#pragma once

#include <core\singleton.h>
#include <core\containers\pointerarray.h>

namespace OK
{
    class BaseComponentFactory;
    class JSONNode;

    using ComponentHolderID = OK::u64;
    using ComponentFactoryID = OK::u64;
    constexpr ComponentHolderID K_INVALID_COMPONENT_HOLDER = 0xFFFFFFFFFFFFFFFF;
    constexpr ComponentFactoryID K_INVALID_COMPONENT_FACTORY = 0xFFFFFFFFFFFFFFFF;

    class ComponentHolder : public Singleton<ComponentHolder>
    {
    public:
        ComponentHolder();
        ~ComponentHolder();

        static EResult LoadEntity(ComponentHolderID entityID, JSONNode* entityNode);
        static ComponentHolderID GetNextComponentHolderID();

    private:
        void RegisterComponentFactories();
        void UnregisterComponentFactories();

        PointerArray<BaseComponentFactory> m_Factories;
    };
}