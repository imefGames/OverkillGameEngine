#pragma once

#include <core\singleton.h>
#include <core\containers\pointerarray.h>
#include <engine\objectmodel\componentholder.h>
#include <engine\objectmodel\world.h>

namespace OK
{
    class GameLoop;
    class World;
    class UniverseSystem;

    class Universe : public Singleton<Universe>
    {
    public:
        Universe();

    private:
        void Init();
        void Shutdown();
        void Update(OK::f32 dt);

        ComponentHolderID m_ComponentHolderID;
        Array<World> m_World;
        PointerArray<UniverseSystem> m_UniverseSystems;

        friend OK::GameLoop;
    };
}