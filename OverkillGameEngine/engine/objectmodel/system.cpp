#include <stdafx.h>
#include <engine\objectmodel\system.h>

#include <engine\objectmodel\subsystem.h>
#include <engine\objectmodel\universe.h>

namespace OK
{
    void System::Init()
    {
    }

    void System::Shutdown()
    {
        for (SubSystem* subSystem : m_SubSystems)
        {
            subSystem->Shutdown();
        }
        m_SubSystems.DeleteAll();
    }

    void System::Update(OK::f32 dt)
    {
        for (SubSystem* subSystem : m_SubSystems)
        {
            subSystem->Update(dt);
        }
    }

    const Array<ComponentHolderID>& System::GetActiveComponentHolders() const
    {
        return Universe::Get()->GetActiveComponentHolders();
    }

    void System::RegisterSubSystem(SubSystem* subSystem)
    {
        subSystem->Init();
        m_SubSystems.Add(subSystem);
    }
}