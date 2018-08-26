#pragma once

#include <engine\objectmodel\subsystem.h>

namespace OK
{
    class LightSubSystem : public SubSystem
    {
    public:
        LightSubSystem(System* owner);

        static ComponentHolderID GetActiveLightomponentHolderID() { return ms_LightComponentHolderID; }

    private:
        void Update(OK::f32 dt) override;

        static ComponentHolderID ms_LightComponentHolderID;
    };
}