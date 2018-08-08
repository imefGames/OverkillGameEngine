#pragma once

#include <engine\objectmodel\system.h>

namespace OK
{
    class UniverseSystem : public System
    {
    protected:
        UniverseSystem() = default;

        const Array<ComponentHolderID>& GetActiveComponentHolders() const;
    };
}