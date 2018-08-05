#include <stdafx.h>
#include <engine\objectmodel\world.h>

#include <engine\objectmodel\worldsystem.h>

namespace OK
{
    World::World()
        : m_ComponentHolderID{ ComponentHolder::GetNextComponentHolderID() }
    {
    }

    void World::Init()
    {
        for (WorldSystem* system : m_WorldSystems)
        {
            system->Init();
        }
    }

    void World::Shutdown()
    {
        for (WorldSystem* system : m_WorldSystems)
        {
            system->Shutdown();
        }
        m_WorldSystems.DeleteAll();
    }

    void World::Update(OK::f32 dt)
    {
        for (WorldSystem* system : m_WorldSystems)
        {
            system->Update(dt);
        }
    }
}