#pragma once

#include <engine\objectmodel\component.h>

namespace OK
{
    class ModelComponent : public Component<ModelComponent>
    {
    public:
        const String& GetModelName() const { return m_ModelName; }
        const String& GetShaderName() const { return m_ShaderName; }
        const String& GetTextureName() const { return m_TextureName; }

    private:
        EResult LoadComponent(JSONNode* componentNode) override;

        String m_ModelName;
        String m_ShaderName;
        String m_TextureName;
    };
}