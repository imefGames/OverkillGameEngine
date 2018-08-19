#pragma once

#include <core\math\vectors.h>
#include <engine\objectmodel\component.h>

namespace OK
{
    class RectTransformComponent : public Component<RectTransformComponent>, public AllocationPolicy<AlignedAllocation<alignof(OK::Vec4)>>
    {
    public:
        OK::Vec4& GetPosition() { return m_Position; }
        const OK::Vec4& GetPosition() const { return m_Position; }
        void SetPosition(const OK::Vec4& newPosition) { m_Position = newPosition; }

        OK::Vec4& GetSize() { return m_Size; }
        const OK::Vec4& GetSize() const { return m_Size; }
        void SetSize(const OK::Vec4& newSize) { m_Size = newSize; }

    private:
        EResult LoadComponent(const JSONNode& componentNode) override;

        OK::Vec4 m_Position;
        OK::Vec4 m_Size;
    };
}