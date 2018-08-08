#pragma once

#include <core\containers\pointerarray.h>
#include <engine\objectmodel\componentholder.h>

namespace OK
{
    class JSONNode;
    class WorldSystem;

    class World
    {
    public:
        World();

        EResult LoadGameData(JSONNode* worldNode);

        void Init();
        void Shutdown();
        void Update(OK::f32 dt);

        const String& GetWorldName() const { return m_WorldName; }
        ComponentHolderID GetComponentHolderID() const { return m_ComponentHolderID; }
        const Array<ComponentHolderID>& GetEntityIDs() const { return m_EntityIDs; }

    private:
        String m_WorldName;
        ComponentHolderID m_ComponentHolderID;
        Array<ComponentHolderID> m_EntityIDs;
        PointerArray<WorldSystem> m_WorldSystems;
    };
}