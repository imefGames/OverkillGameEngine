#include <stdafx.h>
#include <engine\objectmodel\universe.h>

#include <engine\objectmodel\universesystem.h>
#include <engine\objectmodel\world.h>

namespace OK
{
    Universe::Universe()
        : m_ComponentHolderID{ ComponentHolder::GetNextComponentHolderID() }
    {
    }
}