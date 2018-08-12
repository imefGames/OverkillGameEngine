#include <stdafx.h>
#include <engine\objectmodel\world.h>

#include <core\io\parsers\json\jsonnode.h>
#include <engine\objectmodel\worldsystem.h>

namespace OK
{
    World::World()
        : m_ComponentHolderID{ ComponentHolder::GetNextComponentHolderID() }
    {
    }

    EResult World::LoadGameData(const JSONNode& worldNode)
    {
        const JSONNode* worldName = worldNode["Name"];
        const JSONNode* entityList = worldNode["Entities"];

        StringView worldNameView = worldName->GetValue();
        m_WorldName.Resize(worldNameView.GetLength());
        OK::MemCopy(worldNameView.begin(), m_WorldName.begin(), m_WorldName.GetSize());

        m_EntityIDs.Clear();
        m_EntityIDs.Reserve(entityList->GetSubNodeCount());
        for (const JSONNode& componentList : *entityList)
        {
            ComponentHolderID newEntity = m_EntityIDs.Add(ComponentHolder::GetNextComponentHolderID());
            ComponentHolder::LoadComponentList(newEntity, componentList);
        }

        //TODO: load world components

        return EResult::Success;
    }

    void World::Init()
    {
        for (WorldSystem* system : m_WorldSystems)
        {
            system->Init();
        }
    }

    void World::Shutdown()
    {
        for (WorldSystem* system : m_WorldSystems)
        {
            system->Shutdown();
        }
        m_WorldSystems.DeleteAll();
    }

    void World::Update(OK::f32 dt)
    {
        for (WorldSystem* system : m_WorldSystems)
        {
            system->Update(dt);
        }
    }
}