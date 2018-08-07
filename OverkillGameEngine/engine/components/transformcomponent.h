#pragma once

#include <core\math\vectors.h>
#include <engine\objectmodel\component.h>

namespace OK
{
    class TransformComponent : public Component<TransformComponent>
    {
    private:
        EResult LoadComponent(JSONNode* componentNode) override;

        OK::Vec4 m_Position;
    };
}