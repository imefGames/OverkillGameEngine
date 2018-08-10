#pragma once

#include <engine\objectmodel\component.h>

namespace OK
{
    class ModelComponent : public Component<ModelComponent>
    {
    public:
        const String& GetShaderName() const { return m_ShaderName; }
        const String& GetModelName() const { return m_ModelName; }

    private:
        EResult LoadComponent(JSONNode* componentNode) override;

        String m_ShaderName;
        String m_ModelName;
    };
}