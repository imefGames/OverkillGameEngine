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

        OK::Vec4& GetSpecularColor() { return m_SpecularColor; }
        const OK::Vec4& GetSpecularColor() const { return m_SpecularColor; }
        void SetSpecularColor(const OK::Vec4& newSpecularColor) { m_SpecularColor = newSpecularColor; }

        OK::f32 GetSpecularPower() const { return m_SpecularPower; }
        void SetSpecularPower(OK::f32 newSpecularPower) { m_SpecularPower = m_SpecularPower; }

    private:
        EResult LoadComponent(const JSONNode& componentNode) override;

        OK::Vec4 m_AmbientColor;
        OK::Vec4 m_DiffuseColor;
        OK::Vec4 m_SpecularColor;
        OK::f32 m_SpecularPower;
    };
}