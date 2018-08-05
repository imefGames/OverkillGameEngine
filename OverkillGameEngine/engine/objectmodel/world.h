#pragma once

#include <core\containers\pointerarray.h>
#include <engine\objectmodel\componentholder.h>

namespace OK
{
    class WorldSystem;

    class World
    {
    public:
        World();

        void Init();
        void Shutdown();
        void Update(OK::f32 dt);

    private:
        ComponentHolderID m_ComponentHolderID;
        PointerArray<WorldSystem> m_WorldSystems;
    };
}