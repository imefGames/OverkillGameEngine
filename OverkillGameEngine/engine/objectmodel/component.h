#pragma once

#include <engine\objectmodel\componentholder.h>
#include <malloc.h>

namespace OK
{
    class JSONNode;

    class BaseComponent
    {
    public:
        virtual EResult LoadComponent(const JSONNode& componentNode) { return EResult::Success; }

        ComponentHolderID GetHolderID() const { return m_ComponentHolderID; }
        void SetHolderID(ComponentHolderID componentHolderID) { m_ComponentHolderID = componentHolderID; }

    protected:
        BaseComponent();

    private:
        ComponentHolderID m_ComponentHolderID;
    };

    template <typename ComponentType>
    class Component : public BaseComponent
    {
    public:
        static void RegisterComponentFactory(ComponentFactoryID factoryID);
        static void UnregisterComponentFactory();
        static ComponentFactoryID GetFactoryID() { return ms_FactoryID; };

    private:
        static ComponentFactoryID ms_FactoryID;
    };

    template <typename ComponentType>
    ComponentFactoryID Component<ComponentType>::ms_FactoryID = K_INVALID_COMPONENT_FACTORY;

    template <typename ComponentType>
    void Component<ComponentType>::RegisterComponentFactory(ComponentFactoryID factoryID)
    {
        okAssert(ms_FactoryID == K_INVALID_COMPONENT_HOLDER, "Component already has a factory.");
        ms_FactoryID = factoryID;
    }

    template <typename ComponentType>
    void Component<ComponentType>::UnregisterComponentFactory()
    {
        okAssert(ms_FactoryID != K_INVALID_COMPONENT_HOLDER, "Component already has a factory.");
        K_INVALID_COMPONENT_HOLDER = factoryID;
    }
}