#include <stdafx.h>
#include <engine\components\transformcomponent.h>

#include <core\io\parsers\json\jsonnode.h>

namespace OK
{
    EResult TransformComponent::LoadComponent(JSONNode* componentNode)
    {
        okAssert(componentNode != nullptr, "Could not find Component node in game data file.");

        OK::f32 x{ componentNode->GetValue<OK::f32>("x") };
        OK::f32 y{ componentNode->GetValue<OK::f32>("y") };
        OK::f32 z{ componentNode->GetValue<OK::f32>("z") };
        m_Position = Vec4{ x, y, z };

        OK::f32 rx{ componentNode->GetValue<OK::f32>("rx") };
        OK::f32 ry{ componentNode->GetValue<OK::f32>("ry") };
        OK::f32 rz{ componentNode->GetValue<OK::f32>("rz") };
        m_RotationEuler = Vec4{ rx, ry, rz };

        OK::f32 sx{ componentNode->GetValue<OK::f32>("sx") };
        OK::f32 sy{ componentNode->GetValue<OK::f32>("sy") };
        OK::f32 sz{ componentNode->GetValue<OK::f32>("sz") };
        m_Scale= Vec4{ sx, sy, sz };
        return EResult::Success;
    }
}