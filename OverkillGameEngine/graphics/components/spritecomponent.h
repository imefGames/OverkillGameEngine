#pragma once

#include <engine\objectmodel\component.h>

namespace OK
{
    class SpriteComponent : public Component<SpriteComponent>
    {
    public:
        const String& GetShaderName() const { return m_ShaderName; }
        const String& GetTextureName() const { return m_TextureName; }

    private:
        EResult LoadComponent(const JSONNode& componentNode) override;

        String m_ShaderName;
        String m_TextureName;
    };
}