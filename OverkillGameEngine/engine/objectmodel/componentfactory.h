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
        virtual BaseComponent* FindComponentForID(ComponentHolderID holderID) = 0;

        const String& GetName() const { return m_Name; }

    protected:
        BaseComponentFactory(ComponentFactoryID factoryID, const OK::char8* name);

    private:
        String m_Name;
        ComponentFactoryID m_FactoryID;
    };

    template <typename ComponentType>
    class ComponentFactory : public BaseComponentFactory
    {
        static_assert(OK::IsBaseOf<BaseComponent, ComponentType>::value, "ComponentFactory must instanciate classes of type Component.");

    public:
        ComponentFactory(ComponentFactoryID factoryID, const OK::char8* name);
        ~ComponentFactory();

    private:
        BaseComponent& InstanciateComponent() override;
        BaseComponent* FindComponentForID(ComponentHolderID holderID) override;

        Array<ComponentType> m_ComponentPool;
    };

    template<typename ComponentType>
    ComponentFactory<ComponentType>::ComponentFactory(ComponentFactoryID factoryID, const OK::char8* name)
        : BaseComponentFactory{ factoryID, name }
    {
        ComponentType::RegisterComponentFactory(factoryID);
    }

    template<typename ComponentType>
    ComponentFactory<ComponentType>::~ComponentFactory()
    {
        ComponentType::UnregisterComponentFactory();
    }

    template<typename ComponentType>
    BaseComponent& ComponentFactory<ComponentType>::InstanciateComponent()
    {
        ComponentType& newComponent = m_ComponentPool.Grow();
        return newComponent;
    }

    template<typename ComponentType>
    BaseComponent* ComponentFactory<ComponentType>::FindComponentForID(ComponentHolderID holderID)
    {
        auto findByID = [holderID](const ComponentType& component)
        {
            return (component.GetHolderID() == holderID);
        };
        auto foundIt = OK::FindIf(m_ComponentPool.begin(), m_ComponentPool.end(), findByID);
        return (foundIt != m_ComponentPool.end() ? foundIt : nullptr);
    }
}