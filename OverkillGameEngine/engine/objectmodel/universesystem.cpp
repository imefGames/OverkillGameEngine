#include <stdafx.h>
#include <engine\objectmodel\universesystem.h>

#include <engine\objectmodel\universe.h>

namespace OK
{
    const Array<ComponentHolderID>& UniverseSystem::GetActiveComponentHolders() const
    {
        return Universe::Get()->GetActiveComponentHolders();
    }
}