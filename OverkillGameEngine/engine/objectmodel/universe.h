#pragma once

#include <core\containers\pointerarray.h>
#include <engine\objectmodel\componentholder.h>

namespace OK
{
    class World;
    class UniverseSystem;

    class Universe
    {
    public:
        Universe();

    private:
        ComponentHolderID m_ComponentHolderID;
        Array<World> m_World;
        PointerArray<UniverseSystem> m_UniverseSystems;
    };
}