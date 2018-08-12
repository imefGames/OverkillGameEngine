#include <stdafx.h>
#include <graphics\components\cameracomponent.h>

#include <core\io\parsers\json\jsonnode.h>

namespace OK
{
    CameraComponent::CameraComponent()
        : m_IsActive{ false }
    {
    }
    
    EResult CameraComponent::LoadComponent(const JSONNode& componentNode)
    {
        m_IsActive = componentNode.GetValueAs<OK::Bool>("IsActive");
        return EResult::Success;

    }
}