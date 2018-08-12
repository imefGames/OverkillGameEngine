#include <stdafx.h>
#include <engine\components\transformcomponent.h>

#include <core\io\parsers\json\jsonnode.h>

namespace OK
{
    EResult TransformComponent::LoadComponent(const JSONNode& componentNode)
    {
        OK::f32 x{ componentNode.GetValueAs<OK::f32>("x") };
        OK::f32 y{ componentNode.GetValueAs<OK::f32>("y") };
        OK::f32 z{ componentNode.GetValueAs<OK::f32>("z") };
        m_Position = Vec4{ x, y, z };

        OK::f32 rx{ componentNode.GetValueAs<OK::f32>("rx", 0.0f) };
        OK::f32 ry{ componentNode.GetValueAs<OK::f32>("ry", 0.0f) };
        OK::f32 rz{ componentNode.GetValueAs<OK::f32>("rz", 0.0f) };
        m_RotationEuler = Vec4{ rx, ry, rz };

        OK::f32 sx{ componentNode.GetValueAs<OK::f32>("sx", 1.0f) };
        OK::f32 sy{ componentNode.GetValueAs<OK::f32>("sy", 1.0f) };
        OK::f32 sz{ componentNode.GetValueAs<OK::f32>("sz", 1.0f) };
        m_Scale= Vec4{ sx, sy, sz };
        return EResult::Success;
    }
}