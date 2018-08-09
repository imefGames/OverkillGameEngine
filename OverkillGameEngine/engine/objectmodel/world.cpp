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

    EResult World::LoadGameData(JSONNode* worldNode)
    {
        okAssert(worldNode != nullptr, "Could not find World node in game data file.");
        worldNode->ComputeSubNodes();
        JSONNode* worldName = worldNode->GetNode("Name");
        JSONNode* entityList = worldNode->GetNode("Entities");
        okAssert(worldName != nullptr, "Could not find World Name node in game data file.");
        okAssert(entityList != nullptr, "Could not find Entity List node in game data file.");

        worldName->ComputeSubNodes();
        okAssert(worldName->GetNodeType() == JSONNode::ENodeType::Leaf, "World Name node in must be of type Leaf.");
        StringView worldNameView = worldName->GetData();
        m_WorldName.Resize(worldNameView.GetLength());
        OK::MemCopy(worldNameView.begin(), m_WorldName.begin(), m_WorldName.GetSize());

        entityList->ComputeSubNodes();
        okAssert(entityList->GetNodeType() == JSONNode::ENodeType::Array, "Entity List node in must be of type Array.");
        OK::u32 entityCount = entityList->GetArrayNodeSize();
        m_EntityIDs.Clear();
        m_EntityIDs.Reserve(entityList->GetArrayNodeSize());
        for (OK::u32 i = 0; i < entityCount; ++i)
        {
            ComponentHolderID newEntity = m_EntityIDs.Add(ComponentHolder::GetNextComponentHolderID());
            ComponentHolder::LoadComponentList(newEntity, entityList->GetNodeAtIndex(i));
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