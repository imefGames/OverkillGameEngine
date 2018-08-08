#pragma once

#include <core\singleton.h>

namespace OK
{
    class D3DContext;
    class ModelComponent;
    class TransformComponent;
    struct GameWindowData;

    class GraphicsWrapper : public Singleton<GraphicsWrapper>
    {
    public:
        GraphicsWrapper();

        EResult Init(const GameWindowData& windowData);
        void Shutdown();
        void BeginScene();
        void EndScene();

        void RenderModel(const ModelComponent* model, const TransformComponent* transform);
        void SetCameraTransform(const TransformComponent* transform);

    private:
        static const bool K_FULL_SCREEN;
        static const bool K_VSYNC_ENABLED;
        static const float K_SCREEN_DEPTH;
        static const float K_SCREEN_NEAR;

        D3DContext* m_D3DContext;
    };
}