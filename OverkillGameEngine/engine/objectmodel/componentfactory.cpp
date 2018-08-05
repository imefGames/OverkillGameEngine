#include <stdafx.h>
#include <engine\objectmodel\componentfactory.h>

namespace OK
{
    BaseComponentFactory::BaseComponentFactory(ComponentFactoryID factoryID)
        : m_FactoryID{ factoryID }
    {
    }

    template<typename ComponentType>
    BaseComponent& ComponentFactory<ComponentType>::InstanciateComponent()
    {
        ComponentType& newComponent = m_ComponentPool.Grow();
        return newComponent;
    }
}