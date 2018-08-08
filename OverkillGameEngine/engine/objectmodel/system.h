#pragma once

#include <engine\objectmodel\componentholder.h>

namespace OK
{
    class System
    {
    public:
        virtual void Init();
        virtual void Shutdown();
        virtual void Update(OK::f32 dt);
    };
}