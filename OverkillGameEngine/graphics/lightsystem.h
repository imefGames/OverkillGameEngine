#pragma once

#include <engine\objectmodel\universesystem.h>

namespace OK
{
    class LightSystem : public UniverseSystem
    {
    public:
        LightSystem();

        static ComponentHolderID GetActiveLightomponentHolderID() { return ms_LightComponentHolderID; }

    private:
        void Update(OK::f32 dt) override;

        static ComponentHolderID ms_LightComponentHolderID;
    };
}