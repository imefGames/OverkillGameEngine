#include <stdafx.h>
#include <engine\components\recttransformcomponent.h>

#include <core\io\parsers\json\jsonnode.h>

namespace OK
{
    EResult RectTransformComponent::LoadComponent(const JSONNode& componentNode)
    {
        OK::f32 x{ componentNode.GetValueAs<OK::f32>("x") };
        OK::f32 y{ componentNode.GetValueAs<OK::f32>("y") };
        m_Position = Vec4{ x, y };

        OK::f32 sx{ componentNode.GetValueAs<OK::f32>("sx", 1.0f) };
        OK::f32 sy{ componentNode.GetValueAs<OK::f32>("sy", 1.0f) };
        m_Size = Vec4{ sx, sy };
        return EResult::Success;
    }
}