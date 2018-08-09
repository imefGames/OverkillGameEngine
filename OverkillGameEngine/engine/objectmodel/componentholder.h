#pragma once

#include <core\singleton.h>
#include <core\containers\pointerarray.h>

namespace OK
{
    class BaseComponent;
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

        //TODO: rename function. It really loads a component list.
        static EResult LoadComponentList(ComponentHolderID entityID, JSONNode* componentListNode);
        static BaseComponent* FindComponentForID(ComponentHolderID holderID, ComponentFactoryID factoryID);
        static ComponentHolderID GetNextComponentHolderID();

    private:
        void RegisterComponentFactories();
        void UnregisterComponentFactories();

        PointerArray<BaseComponentFactory> m_Factories;
    };
}