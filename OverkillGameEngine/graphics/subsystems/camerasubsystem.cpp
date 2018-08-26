#include <stdafx.h>
#include <graphics\subsystems\camerasubsystem.h>

#include <engine\objectmodel\componentutils.h>
#include <graphics\components\cameracomponent.h>

namespace OK
{
    ComponentHolderID CameraSubSystem::ms_CameraComponentHolderID = K_INVALID_COMPONENT_HOLDER;

    CameraSubSystem::CameraSubSystem(System* owner)
        : SubSystem{ owner }
    {
    }

    void CameraSubSystem::Update(OK::f32 dt)
    {
        ms_CameraComponentHolderID = K_INVALID_COMPONENT_HOLDER;
        const Array<ComponentHolderID>& activeHolderIDs{ GetActiveComponentHolders() };
        for (ComponentHolderID holderID : activeHolderIDs)
        {
            CameraComponent* camera{ nullptr };
            if (ComponentUtils::FindComponents(holderID, camera) == EResult::Success && camera->IsActive())
            {
                ms_CameraComponentHolderID = holderID;
                break;
            }
        }
    }

}