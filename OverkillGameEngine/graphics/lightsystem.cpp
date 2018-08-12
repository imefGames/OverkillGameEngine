#include <stdafx.h>
#include <graphics\lightsystem.h>

#include <engine\objectmodel\componentutils.h>
#include <graphics\components\lightsourcecomponent.h>

namespace OK
{
    ComponentHolderID LightSystem::ms_LightComponentHolderID = K_INVALID_COMPONENT_HOLDER;

    LightSystem::LightSystem()
    {
    }

    void LightSystem::Update(OK::f32 dt)
    {
        ms_LightComponentHolderID = K_INVALID_COMPONENT_HOLDER;
        const Array<ComponentHolderID>& activeHolderIDs{ GetActiveComponentHolders() };
        for (ComponentHolderID holderID : activeHolderIDs)
        {
            LightSourceComponent* lightSource{ nullptr };
            if (ComponentUtils::FindComponents(holderID, lightSource) == EResult::Success)
            {
                ms_LightComponentHolderID = holderID;
                break;
            }
        }
    }

}