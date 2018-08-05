#pragma once

#include <core\containers\array.h>
#include <engine\objectmodel\component.h>
#include <engine\objectmodel\componentholder.h>

namespace OK
{
    class BaseComponentFactory
    {
    public:
        virtual BaseComponent& InstanciateComponent() = 0;

    protected:
        BaseComponentFactory(ComponentFactoryID factoryID);

    private:
        ComponentFactoryID m_FactoryID;
    };

    template <typename ComponentType>
    class ComponentFactory
    {
        static_assert(OK::IsBaseOf<BaseComponent, ComponentType>::value, "ComponentFactory must instanciate classes of type Component.");

    public:
        ComponentFactory(ComponentFactoryID factoryID);
        ~ComponentFactory();

    private:
        BaseComponent& InstanciateComponent() override;

        Array<ComponentType> m_ComponentPool;
    };

    template<typename ComponentType>
    ComponentFactory<ComponentType>::ComponentFactory(ComponentFactoryID factoryID)
        : BaseComponentFactory{ factoryID }
    {
        ComponentType::RegisterComponentFactory(factoryID);
    }

    template<typename ComponentType>
    ComponentFactory<ComponentType>::~ComponentFactory()
    {
        ComponentType::UnregisterComponentFactory();
    }
}