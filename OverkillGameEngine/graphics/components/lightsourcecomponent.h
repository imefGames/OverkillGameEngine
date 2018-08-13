#pragma once

#include <core\math\vectors.h>
#include <engine\objectmodel\component.h>

namespace OK
{
    class LightSourceComponent : public Component<LightSourceComponent>, public AllocationPolicy<AlignedAllocation<alignof(OK::Vec4)>>
    {
    public:
        OK::Vec4& GetDiffuseColor() { return m_DiffuseColor; }
        const OK::Vec4& GetDiffuseColor() const { return m_DiffuseColor; }
        void GetDiffuseColor(const OK::Vec4& newDiffuseColor) { m_DiffuseColor = newDiffuseColor; }

    private:
        EResult LoadComponent(const JSONNode& componentNode) override;

        OK::Vec4 m_DiffuseColor;
    };
}