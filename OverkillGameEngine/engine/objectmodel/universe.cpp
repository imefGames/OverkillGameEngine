#include <stdafx.h>
#include <engine\objectmodel\universe.h>

#include <core\io\parsers\json\jsonnode.h>
#include <engine\objectmodel\universesystem.h>
#include <graphics\camerasystem.h>
#include <graphics\graphicssystem.h>

namespace OK
{
    Universe::Universe()
        : m_CurrentWorld{ nullptr }
        , m_ComponentHolderID{ ComponentHolder::GetNextComponentHolderID() }
    {
    }

    EResult Universe::LoadGameData(JSONNode* universeNode)
    {
        okAssert(universeNode != nullptr, "Could not find Universe node in game data file.");
        universeNode->ComputeSubNodes();
        JSONNode* worldList = universeNode->GetNode("Worlds");
        JSONNode* startupWorld = universeNode->GetNode("StartupWorld");
        okAssert(worldList != nullptr, "Could not find World List node in game data file.");
        okAssert(startupWorld != nullptr, "Could not find Startup World node in game data file.");

        worldList->ComputeSubNodes();
        startupWorld->ComputeSubNodes();
        okAssert(worldList->GetNodeType() == JSONNode::ENodeType::Array, "World List node in must be of type Array.");
        okAssert(startupWorld->GetNodeType() == JSONNode::ENodeType::Leaf, "Startup World node in must be of type Leaf.");

        OK::u32 worldListSize = worldList->GetArrayNodeSize();
        for (OK::u32 i = 0; i < worldListSize; ++i)
        {
            JSONNode* worldNode = worldList->GetNodeAtIndex(i);
            World& newWorld = m_Worlds.Grow();
            newWorld.LoadGameData(worldNode);
        }

        StringView startupWorldName = startupWorld->GetData();
        auto findByName = [startupWorldName](const World& currentWorld)
        {
            return startupWorldName == currentWorld.GetWorldName().begin();
        };
        m_CurrentWorld = OK::FindIf(m_Worlds.begin(), m_Worlds.end(), findByName);
        okAssert(m_CurrentWorld != m_Worlds.end(), "Could not find startup world.");

        ComponentHolder::LoadComponentList(m_ComponentHolderID, universeNode);

        return EResult::Success;
    }

    void Universe::Init()
    {
        m_UniverseSystems.Add(new CameraSystem);
        m_UniverseSystems.Add(new GraphicsSystem);

        for (UniverseSystem* system : m_UniverseSystems)
        {
            system->Init();
        }
        for (World& world : m_Worlds)
        {
            world.Init();
        }
    }

    void Universe::Shutdown()
    {
        for (UniverseSystem* system : m_UniverseSystems)
        {
            system->Shutdown();
        }
        m_UniverseSystems.DeleteAll();

        for (World& world : m_Worlds)
        {
            world.Shutdown();
        }
        m_Worlds.Clear();
    }

    void Universe::Update(OK::f32 dt)
    {
        ResetActiveComponentHolderList();

        for (UniverseSystem* system : m_UniverseSystems)
        {
            system->Update(dt);
        }

        okAssert(m_CurrentWorld != nullptr, "Universe has no current world.");
        if (m_CurrentWorld != nullptr)
        {
            m_CurrentWorld->Update(dt);
        }
    }

    void Universe::ResetActiveComponentHolderList()
    {
        okAssert(m_CurrentWorld != nullptr, "Universe has no current world.");
        const Array<ComponentHolderID>& worldEntities = m_CurrentWorld->GetEntityIDs();

        m_ActiveComponentHolderIDs.Clear();
        m_ActiveComponentHolderIDs.Reserve(worldEntities.GetSize() + 2); // doing +2 for universe & world
        m_ActiveComponentHolderIDs.Add(m_ComponentHolderID);
        ComponentHolderID worldComponentHolderID = m_CurrentWorld->GetComponentHolderID();
        m_ActiveComponentHolderIDs.Add(worldComponentHolderID);

        for (const ComponentHolderID& entityHolderID : worldEntities)
        {
            m_ActiveComponentHolderIDs.Add(entityHolderID);
        }
    }
}