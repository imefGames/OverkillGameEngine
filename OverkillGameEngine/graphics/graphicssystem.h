#pragma once

#include <engine\objectmodel\universesystem.h>

namespace OK
{
    class GraphicsWrapper;

    class GraphicsSystem : public UniverseSystem
    {
    public:
        GraphicsSystem();

    private:
        void Init() override;
        void Shutdown() override;
        void Update(OK::f32 dt) override;

        GraphicsWrapper* m_GraphicsWrapper;
    };
}