#pragma once

#include <core\singleton.h>
#include <graphics\renderingcontext.h>
#include <graphics\model\modellibrary.h>
#include <graphics\shaders\shaderlibrary.h>
#include <graphics\texture\texturelibrary.h>

namespace OK
{
    class D3DContext;
    class JSONNode;
    class LightSourceComponent;
    class ModelComponent;
    class RectTransformComponent;
    class SpriteComponent;
    class TransformComponent;
    struct GameWindowData;

    class GraphicsWrapper : public Singleton<GraphicsWrapper>
    {
    public:
        GraphicsWrapper();
        ~GraphicsWrapper();

        EResult Init(const GameWindowData& windowData);
        void Shutdown();
        void BeginScene(const TransformComponent* cameraTransform);
        void EndScene();

        void SetLight(LightSourceComponent* lightComponent, TransformComponent* lightTransform);

        EResult RegisterModels(const JSONNode& modelListNode);
        EResult RegisterTextures(const JSONNode& textureNode);
        void RenderModel(const ModelComponent* model, const TransformComponent* transform);
        void RenderSprite(const SpriteComponent* sprite, const RectTransformComponent* transform);

        void Begin2DRenderingPass();
        void End2DRenderingPass();

    private:
        static const bool K_FULL_SCREEN;
        static const bool K_VSYNC_ENABLED;
        static const float K_SCREEN_DEPTH;
        static const float K_SCREEN_NEAR;

        D3DContext* m_D3DContext;
        RenderingContext* m_RenderingContext;
        ModelLibrary m_ModelLibrary;
        ShaderLibrary m_ShaderLibrary;
        TextureLibrary m_TextureLibrary;
    };
}