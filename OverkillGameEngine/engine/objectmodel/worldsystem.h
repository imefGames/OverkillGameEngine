#pragma once

#include <engine\objectmodel\system.h>

namespace OK
{
    class World;

    class WorldSystem : public System
    {
    protected:
        WorldSystem() = delete;
        WorldSystem(World* owner);
    private:
        World* m_OwnerWorld;
    };
}