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

    private:
        String m_WorldName;
        ComponentHolderID m_ComponentHolderID;
        PointerArray<WorldSystem> m_WorldSystems;
    };
}