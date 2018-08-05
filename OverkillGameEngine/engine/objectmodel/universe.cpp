#include <stdafx.h>
#include <engine\objectmodel\universe.h>

#include <engine\objectmodel\universesystem.h>
#include <graphics\graphicssystem.h>

namespace OK
{
    Universe::Universe()
        : m_CurrentWorld{ nullptr }
        , m_ComponentHolderID{ ComponentHolder::GetNextComponentHolderID() }
    {
    }


    void Universe::Init()
    {
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
        for (UniverseSystem* system : m_UniverseSystems)
        {
            system->Update(dt);
        }

        //TODO: re-use assert once we have worlds
        //okAssert(m_CurrentWorld != nullptr, "Universe has no current world.");
        if (m_CurrentWorld != nullptr)
        {
            m_CurrentWorld->Update(dt);
        }
    }
}