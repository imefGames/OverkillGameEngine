#pragma once

#include <core\math\vectors.h>
#include <engine\objectmodel\component.h>

namespace OK
{
    class TransformComponent : public Component<TransformComponent>, public AllocationPolicy<AlignedAllocation<alignof(OK::Vec4)>>
    {
    public:
        OK::Vec4& GetPosition() { return m_Position; }
        const OK::Vec4& GetPosition() const { return m_Position; }
        void SetPosition(const OK::Vec4& newPosition) { m_Position = newPosition; }

        OK::Vec4& GetRotationEuler() { return m_RotationEuler; }
        const OK::Vec4& GetRotationEuler() const { return m_RotationEuler; }
        void SetRotationEuler(const OK::Vec4& newRotationEuler) { m_RotationEuler = newRotationEuler; }

        OK::Vec4& GetScale() { return m_Scale; }
        const OK::Vec4& GetScale() const { return m_Scale; }
        void SetScale(const OK::Vec4& newScale) { m_Scale = newScale; }

    private:
        EResult LoadComponent(const JSONNode& componentNode) override;

        OK::Vec4 m_Position;
        OK::Vec4 m_RotationEuler;
        OK::Vec4 m_Scale;
    };
}