#pragma once

#include <core\math\vectors.h>
#include <engine\objectmodel\component.h>

namespace OK
{
    class LightSourceComponent : public Component<LightSourceComponent>, public AllocationPolicy<AlignedAllocation<alignof(OK::Vec4)>>
    {
    public:
        OK::Vec4& GetAmbientColor() { return m_AmbientColor; }
        const OK::Vec4& GetAmbientColor() const { return m_AmbientColor; }
        void SetAmbientColor(const OK::Vec4& newAmbientColor) { m_AmbientColor = newAmbientColor; }

        OK::Vec4& GetDiffuseColor() { return m_DiffuseColor; }
        const OK::Vec4& GetDiffuseColor() const { return m_DiffuseColor; }
        void SetDiffuseColor(const OK::Vec4& newDiffuseColor) { m_DiffuseColor = newDiffuseColor; }

    private:
        EResult LoadComponent(const JSONNode& componentNode) override;

        OK::Vec4 m_AmbientColor;
        OK::Vec4 m_DiffuseColor;
    };
}