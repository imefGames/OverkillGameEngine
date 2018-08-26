#include <stdafx.h>
#include <engine\objectmodel\subsystem.h>

namespace OK
{
    SubSystem::SubSystem(System* owner)
        : m_OwnerSystem{ owner }
    {
    }
}