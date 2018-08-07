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
        return EResult::Success;
    }
}