#pragma once

#include <core\math\vectors.h>
#include <engine\objectmodel\component.h>

namespace OK
{
    class TransformComponent : public Component<TransformComponent>
    {
    public:
        const OK::Vec4& GetPosition() const { return m_Position; }
        const OK::Vec4& GetRotationEuler() const { return m_RotationEuler; }
        const OK::Vec4& GetScale() const { return m_Scale; }

    private:
        EResult LoadComponent(JSONNode* componentNode) override;

        OK::Vec4 m_Position;
        OK::Vec4 m_RotationEuler;
        OK::Vec4 m_Scale;
    };
}