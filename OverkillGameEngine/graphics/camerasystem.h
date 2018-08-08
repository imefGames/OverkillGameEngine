#pragma once

#include <engine\objectmodel\universesystem.h>

namespace OK
{
    class CameraSystem : public UniverseSystem
    {
    public:
        CameraSystem();

        static ComponentHolderID GetActiveCameraComponentHolderID() { return ms_CameraComponentHolderID; }

    private:
        void Update(OK::f32 dt) override;

        static ComponentHolderID ms_CameraComponentHolderID;
    };
}