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
        okAssert(worldName != nullptr, "Could not find World Name node in game data file.");

        worldName->ComputeSubNodes();
        okAssert(worldName->GetNodeType() == JSONNode::ENodeType::Leaf, "World Name node in must be of type Leaf.");
        StringView worldNameView = worldName->GetData();
        m_WorldName.Resize(worldNameView.GetLength());
        OK::MemCopy(worldNameView.begin(), m_WorldName.begin(), m_WorldName.GetSize());

        //TODO: load world components
        //TODO: instanciate entities

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