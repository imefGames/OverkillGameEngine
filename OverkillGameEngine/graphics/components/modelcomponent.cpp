#include <stdafx.h>
#include <graphics\components\modelcomponent.h>

#include <core\io\parsers\json\jsonnode.h>

namespace OK
{
    EResult ModelComponent::LoadComponent(JSONNode* componentNode)
    {
        okAssert(componentNode != nullptr, "Could not find Component node in game data file.");

        JSONNode* modelName = componentNode->GetNode("ModelName");
        JSONNode* shaderName = componentNode->GetNode("ShaderName");
        JSONNode* textureName = componentNode->GetNode("TextureName");

        m_ModelName.Resize(modelName->GetData().GetLength());
        m_ShaderName.Resize(shaderName->GetData().GetLength());
        m_TextureName.Resize(textureName->GetData().GetLength());
        OK::MemCopy(modelName->GetData().begin(), m_ModelName.begin(), m_ModelName.GetSize());
        OK::MemCopy(shaderName->GetData().begin(), m_ShaderName.begin(), m_ShaderName.GetSize());
        OK::MemCopy(textureName->GetData().begin(), m_TextureName.begin(), m_TextureName.GetSize());

        return EResult::Success;
    }
}