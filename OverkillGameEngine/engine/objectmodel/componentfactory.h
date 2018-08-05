#pragma once

#include <core\containers\array.h>
#include <engine\objectmodel\component.h>

namespace OK
{
    class Component;

    class BaseComponentFactory
    {
    public:
        virtual Component& InstanciateComponent() = 0;
    };

    template <typename ComponentType>
    class ComponentFactory
    {
        static_assert(OK::IsBaseOf<Component, ComponentType>::value, "ComponentFactory must instanciate classes of type Component.");

    private:
        Component& InstanciateComponent() override;

        Array<ComponentType> m_ComponentPool;
    };
}