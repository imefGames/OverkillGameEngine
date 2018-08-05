#include <stdafx.h>
#include <engine\objectmodel\componentfactory.h>

namespace OK
{
    template<typename ComponentType>
    Component& ComponentFactory<ComponentType>::InstanciateComponent()
    {
        ComponentType& newComponent = m_ComponentPool.Grow();
        return newComponent;
    }
}