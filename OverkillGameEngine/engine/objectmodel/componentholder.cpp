#include <stdafx.h>
#include <engine\objectmodel\componentholder.h>

#include <core\io\parsers\json\jsonnode.h>
#include <engine\objectmodel\componentfactory.h>

#include <engine\components\transformcomponent.h>
#include <graphics\components\cameracomponent.h>
#include <graphics\components\modelcomponent.h>
#include <graphics\model\modellibrarycomponent.h>
#include <graphics\texture\texturelibrarycomponent.h>

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

    EResult ComponentHolder::LoadComponentList(ComponentHolderID entityID, JSONNode* componentListNode)
    {
        EResult loadResult{ EResult::Success };
        ComponentHolder* componentHolder = ComponentHolder::Get();

        okAssert(componentListNode != nullptr, "Could not find Entity node in game data file.");
        componentListNode->ComputeSubNodes();

        JSONNode* componentList = componentListNode->GetNode("Components");
        okAssert(componentList != nullptr, "Could not find Component List node in game data file.");

        componentList->ComputeSubNodes();
        okAssert(componentList->GetNodeType() == JSONNode::ENodeType::Array, "Component List node in must be of type Array.");
        OK::u32 componentCount = componentList->GetArrayNodeSize();
        for (OK::u32 i = 0; i < componentCount; ++i)
        {
            JSONNode* currentComponent = componentList->GetNodeAtIndex(i);
            currentComponent->ComputeSubNodes();

            JSONNode* componentName = currentComponent->GetNode("Name");
            okAssert(componentName != nullptr, "Could not find Component Name node in game data file.");
            componentName->ComputeSubNodes();
            okAssert(componentName->GetNodeType() == JSONNode::ENodeType::Leaf, "Component Name node in must be of type Leaf.");

            StringView startupWorldName = componentName->GetData();
            auto findByName = [startupWorldName](BaseComponentFactory* currentFactory)
            {
                return startupWorldName == currentFactory->GetName().begin();
            };
            auto foundIt = OK::FindIf(componentHolder->m_Factories.begin(), componentHolder->m_Factories.end(), findByName);
            BaseComponentFactory* foundFactory = (foundIt != componentHolder->m_Factories.end() ? *foundIt : nullptr);
            if (foundFactory != nullptr)
            {
                BaseComponent& newComponent = foundFactory->InstanciateComponent();
                newComponent.SetHolderID(entityID);
                newComponent.LoadComponent(currentComponent);
            }
            else
            {
                loadResult = EResult::Failure;
            }
        }

        return loadResult;
    }

    BaseComponent* ComponentHolder::FindComponentForID(ComponentHolderID holderID, ComponentFactoryID factoryID)
    {
        ComponentHolder* componentHolder = ComponentHolder::Get();
        okAssert(factoryID < componentHolder->m_Factories.GetSize(), "Invalid Component factory ID.");
        BaseComponentFactory* foundFactory = componentHolder->m_Factories[static_cast<u32>(factoryID)];
        return foundFactory->FindComponentForID(holderID);
    }

    ComponentHolderID ComponentHolder::GetNextComponentHolderID()
    {
        static ComponentHolderID currentComponentHolderID;
        return ++currentComponentHolderID;
    }

    void ComponentHolder::RegisterComponentFactories()
    {
        //TODO: fix json parser to avoid weird names like that...
        m_Factories.Add(new ComponentFactory<TransformComponent>(m_Factories.GetSize(), " \"Transform\""));
        m_Factories.Add(new ComponentFactory<CameraComponent>(m_Factories.GetSize(), " \"Camera\""));
        m_Factories.Add(new ComponentFactory<ModelComponent>(m_Factories.GetSize(), " \"Model\""));
        m_Factories.Add(new ComponentFactory<ModelLibraryComponent>(m_Factories.GetSize(), " \"ModelLibrary\""));
        m_Factories.Add(new ComponentFactory<TextureLibraryComponent>(m_Factories.GetSize(), " \"TextureLibrary\""));
    }

    void ComponentHolder::UnregisterComponentFactories()
    {
        m_Factories.DeleteAll();
    }
}