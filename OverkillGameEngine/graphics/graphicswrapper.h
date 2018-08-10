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
    class ModelComponent;
    class TransformComponent;
    struct GameWindowData;

    class GraphicsWrapper : public Singleton<GraphicsWrapper>
    {
    public:
        GraphicsWrapper();

        EResult Init(const GameWindowData& windowData);
        void Shutdown();
        void BeginScene(const TransformComponent* cameraTransform);
        void EndScene();

        EResult RegisterModels(JSONNode* modelListNode);
        EResult RegisterTextures(JSONNode* textureNode);
        void RenderModel(const ModelComponent* model, const TransformComponent* transform);

    private:
        static const bool K_FULL_SCREEN;
        static const bool K_VSYNC_ENABLED;
        static const float K_SCREEN_DEPTH;
        static const float K_SCREEN_NEAR;

        D3DContext* m_D3DContext;
        RenderingContext m_RenderingContext;
        ModelLibrary m_ModelLibrary;
        ShaderLibrary m_ShaderLibrary;
        TextureLibrary m_TextureLibrary;
    };
}