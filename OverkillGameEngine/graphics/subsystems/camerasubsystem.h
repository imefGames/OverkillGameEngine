#pragma once

#include <engine\objectmodel\subsystem.h>

namespace OK
{
    class CameraSubSystem : public SubSystem
    {
    public:
        CameraSubSystem(System* owner);

        static ComponentHolderID GetActiveCameraComponentHolderID() { return ms_CameraComponentHolderID; }

    private:
        void Update(OK::f32 dt) override;

        static ComponentHolderID ms_CameraComponentHolderID;
    };
}