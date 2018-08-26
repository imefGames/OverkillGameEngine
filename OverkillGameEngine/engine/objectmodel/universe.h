#pragma once

#include <core\singleton.h>
#include <core\containers\pointerarray.h>
#include <engine\objectmodel\componentholder.h>
#include <engine\objectmodel\world.h>

namespace OK
{
    class GameLoop;
    class JSONNode;
    class System;
    class World;
    class UniverseSystem;

    class Universe : public Singleton<Universe>
    {
    public:
        Universe();

        EResult LoadGameData(const JSONNode& universeNode);

    private:
        void Init();
        void Shutdown();
        void Update(OK::f32 dt);

        const Array<ComponentHolderID>& GetActiveComponentHolders() const { return m_ActiveComponentHolderIDs; }
        void ResetActiveComponentHolderList();

        ComponentHolderID m_ComponentHolderID;
        Array<World> m_Worlds;
        World* m_CurrentWorld;
        PointerArray<UniverseSystem> m_UniverseSystems;
        Array<ComponentHolderID> m_ActiveComponentHolderIDs;

        friend OK::GameLoop;
        friend OK::System;
    };
}