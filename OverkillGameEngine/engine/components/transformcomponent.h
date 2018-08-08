#pragma once

#include <core\math\vectors.h>
#include <engine\objectmodel\component.h>

namespace OK
{
    class TransformComponent : public Component<TransformComponent>
    {
    public:
        const OK::Vec4& GetPosition() const { return m_Position; }

    private:
        EResult LoadComponent(JSONNode* componentNode) override;

        OK::Vec4 m_Position;
    };
}