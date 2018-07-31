#pragma once

#include <core\containers\pointerarray.h>

namespace OK
{
    class World;
    class UniverseSystem;

    class Universe
    {
    private:
        Array<World> m_World;
        PointerArray<UniverseSystem> m_UniverseSystems;
    };
}