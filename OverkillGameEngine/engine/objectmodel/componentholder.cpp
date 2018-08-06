#include <stdafx.h>
#include <engine\objectmodel\componentholder.h>

#include <engine\objectmodel\componentfactory.h>

#include <engine\components\transformcomponent.h>
#include <graphics\components\cameracomponent.h>
#include <graphics\components\modelcomponent.h>

namespace OK
{
    ComponentHolder::ComponentHolder()
    {
        RegisterComponentFactories();
    }

    ComponentHolder::~ComponentHolder()
    {
        UnregisterComponentFactories();
    }

    ComponentHolderID ComponentHolder::GetNextComponentHolderID()
    {
        static ComponentHolderID currentComponentHolderID;
        return ++currentComponentHolderID;
    }

    void ComponentHolder::RegisterComponentFactories()
    {
        m_Factories.Add(new ComponentFactory<TransformComponent>(m_Factories.GetSize()));
        m_Factories.Add(new ComponentFactory<CameraComponent>(m_Factories.GetSize()));
        m_Factories.Add(new ComponentFactory<ModelComponent>(m_Factories.GetSize()));
    }

    void ComponentHolder::UnregisterComponentFactories()
    {
        m_Factories.DeleteAll();
    }
}