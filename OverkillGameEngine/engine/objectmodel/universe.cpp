#include <stdafx.h>
#include <engine\objectmodel\universe.h>

#include <core\io\parsers\json\jsonnode.h>
#include <engine\objectmodel\universesystem.h>
#include <graphics\camerasystem.h>
#include <graphics\graphicssystem.h>
#include <graphics\lightsystem.h>

namespace OK
{
    Universe::Universe()
        : m_CurrentWorld{ nullptr }
        , m_ComponentHolderID{ ComponentHolder::GetNextComponentHolderID() }
    {
    }

    EResult Universe::LoadGameData(const JSONNode& universeNode)
    {
        const JSONNode* worldList = universeNode["Worlds"];
        const JSONNode* startupWorld = universeNode["StartupWorld"];

        for (const JSONNode& worldNode : *worldList)
        {
            World& newWorld = m_Worlds.Grow();
            newWorld.LoadGameData(worldNode);
        }

        StringView startupWorldName = startupWorld->GetValue();
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
        m_UniverseSystems.Add(new LightSystem);
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