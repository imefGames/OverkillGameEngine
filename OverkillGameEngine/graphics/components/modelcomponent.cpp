#include <stdafx.h>
#include <graphics\components\modelcomponent.h>

#include <core\io\parsers\json\jsonnode.h>

namespace OK
{
    EResult ModelComponent::LoadComponent(const JSONNode& componentNode)
    {
        const JSONNode* modelName = componentNode["ModelName"];
        const JSONNode* shaderName = componentNode["ShaderName"];
        const JSONNode* textureName = componentNode["TextureName"];

        m_ModelName.Resize(modelName->GetValue().GetLength());
        m_ShaderName.Resize(shaderName->GetValue().GetLength());
        m_TextureName.Resize(textureName->GetValue().GetLength());
        OK::MemCopy(modelName->GetValue().begin(), m_ModelName.begin(), m_ModelName.GetSize());
        OK::MemCopy(shaderName->GetValue().begin(), m_ShaderName.begin(), m_ShaderName.GetSize());
        OK::MemCopy(textureName->GetValue().begin(), m_TextureName.begin(), m_TextureName.GetSize());

        return EResult::Success;
    }
}