#pragma once

#include <core\containers\pointerarray.h>

namespace OK
{
    class WorldSystem;

    class World
    {
    private:
        PointerArray<WorldSystem> m_WorldSystems;
    };
}