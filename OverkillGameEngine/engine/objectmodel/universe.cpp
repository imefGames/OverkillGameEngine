#include <stdafx.h>
#include <engine\objectmodel\universe.h>

#include <engine\objectmodel\universesystem.h>

namespace OK
{
    Universe::Universe()
        : m_CurrentWorld{ nullptr }
        , m_ComponentHolderID{ ComponentHolder::GetNextComponentHolderID() }
    {
    }


    void Universe::Init()
    {
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

        okAssert(m_CurrentWorld != nullptr, "Universe has no current world.");
        if (m_CurrentWorld != nullptr)
        {
            m_CurrentWorld->Update(dt);
        }
    }
}