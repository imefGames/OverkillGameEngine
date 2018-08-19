#include <stdafx.h>
#include <graphics\components\spritecomponent.h>

#include <core\io\parsers\json\jsonnode.h>

namespace OK
{
    EResult SpriteComponent::LoadComponent(const JSONNode& componentNode)
    {
        const JSONNode* shaderName = componentNode["ShaderName"];
        const JSONNode* textureName = componentNode["TextureName"];
        m_ShaderName.Resize(shaderName->GetValue().GetLength());
        m_TextureName.Resize(textureName->GetValue().GetLength());
        OK::MemCopy(shaderName->GetValue().begin(), m_ShaderName.begin(), m_ShaderName.GetSize());
        OK::MemCopy(textureName->GetValue().begin(), m_TextureName.begin(), m_TextureName.GetSize());

        return EResult::Success;
    }
}