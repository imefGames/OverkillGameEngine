#include <stdafx.h>
#include <graphics\components\modelcomponent.h>

#include <core\io\parsers\json\jsonnode.h>

namespace OK
{
    EResult ModelComponent::LoadComponent(JSONNode* componentNode)
    {
        okAssert(componentNode != nullptr, "Could not find Component node in game data file.");

        JSONNode* shaderName = componentNode->GetNode("ShaderName");
        JSONNode* modelName = componentNode->GetNode("ModelName");

        m_ShaderName.Resize(shaderName->GetData().GetLength());
        m_ModelName.Resize(modelName->GetData().GetLength());
        OK::MemCopy(shaderName->GetData().begin(), m_ShaderName.begin(), m_ShaderName.GetSize());
        OK::MemCopy(modelName->GetData().begin(), m_ModelName.begin(), m_ModelName.GetSize());

        return EResult::Success;
    }
}