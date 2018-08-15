#include <stdafx.h>
#include <graphics\components\lightsourcecomponent.h>

#include <core\io\parsers\json\jsonnode.h>

namespace OK
{
    EResult LightSourceComponent::LoadComponent(const JSONNode& componentNode)
    {
        OK::f32 acr{ componentNode.GetValueAs<OK::f32>("acr") };
        OK::f32 acg{ componentNode.GetValueAs<OK::f32>("acg") };
        OK::f32 acb{ componentNode.GetValueAs<OK::f32>("acb") };
        OK::f32 aca{ componentNode.GetValueAs<OK::f32>("aca") };
        m_AmbientColor = Vec4{ acr, acg, acb, aca };

        OK::f32 dcr{ componentNode.GetValueAs<OK::f32>("dcr") };
        OK::f32 dcg{ componentNode.GetValueAs<OK::f32>("dcg") };
        OK::f32 dcb{ componentNode.GetValueAs<OK::f32>("dcb") };
        OK::f32 dca{ componentNode.GetValueAs<OK::f32>("dca") };
        m_DiffuseColor = Vec4{ dcr, dcg, dcb, dca };
        return EResult::Success;
    }
}