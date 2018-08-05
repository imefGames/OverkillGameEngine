#pragma once

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