#include <stdafx.h>
#include <engine\objectmodel\universe.h>

#include <engine\objectmodel\universesystem.h>

namespace OK
{
    Universe::Universe()
        : m_ComponentHolderID{ ComponentHolder::GetNextComponentHolderID() }
    {
    }


    void Universe::Init()
    {
    }

    void Universe::Shutdown()
    {
    }

    void Universe::Update(OK::f32 dt)
    {
    }
}