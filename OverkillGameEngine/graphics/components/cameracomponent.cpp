#include <stdafx.h>
#include <graphics\components\cameracomponent.h>

#include <core\io\parsers\json\jsonnode.h>

namespace OK
{
    CameraComponent::CameraComponent()
        : m_IsActive{ false }
    {
    }
    
    EResult CameraComponent::LoadComponent(JSONNode* componentNode)
    {
        okAssert(componentNode != nullptr, "Could not find Component node in game data file.");

        m_IsActive = componentNode->GetValue<OK::Bool>("IsActive");
        return EResult::Success;

    }
}