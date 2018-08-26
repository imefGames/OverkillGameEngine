#pragma once

#include <engine\objectmodel\componentholder.h>

namespace OK
{
    class SubSystem;

    class System
    {
    public:
        virtual void Init();
        virtual void Shutdown();
        virtual void Update(OK::f32 dt);

        const Array<ComponentHolderID>& GetActiveComponentHolders() const;

    protected:
        template <typename SubSystemType>
        void RegisterSubSystem()
        {
            RegisterSubSystem(new SubSystemType(this));
        }

        void RegisterSubSystem(SubSystem* subSystem);

    private:
        PointerArray<SubSystem> m_SubSystems;
    };
}