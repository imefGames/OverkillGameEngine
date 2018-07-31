#include <engine\objectmodel\world.h>

#include <engine\objectmodel\worldsystem.h>

namespace OK
{
    World::World()
        : m_ComponentHolderID{ ComponentHolderHelper::GetNextComponentHolderID() }
    {
    }
}