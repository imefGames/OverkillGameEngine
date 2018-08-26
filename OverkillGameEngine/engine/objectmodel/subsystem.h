#pragma once

#include <engine\objectmodel\system.h>

namespace OK
{
    class SubSystem : public System
    {
    protected:
        SubSystem() = delete;
        SubSystem(System* owner);
    private:
        System* m_OwnerSystem;
    };
}