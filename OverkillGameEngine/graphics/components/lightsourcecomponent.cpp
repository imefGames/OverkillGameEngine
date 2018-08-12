#include <stdafx.h>
#include <graphics\components\lightsourcecomponent.h>

#include <core\io\parsers\json\jsonnode.h>

namespace OK
{
    EResult LightSourceComponent::LoadComponent(const JSONNode& componentNode)
    {
        OK::f32 r{ componentNode.GetValueAs<OK::f32>("dcr") };
        OK::f32 g{ componentNode.GetValueAs<OK::f32>("dcg") };
        OK::f32 b{ componentNode.GetValueAs<OK::f32>("dcb") };
        OK::f32 a{ componentNode.GetValueAs<OK::f32>("dca") };
        m_DiffuseColor = Vec4{ r, g, b, a };
        return EResult::Success;
    }
}