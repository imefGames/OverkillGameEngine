#include <stdafx.h>
#include <graphics\graphicswrapper.h>

#include <engine\components\transformcomponent.h>
#include <engine\window\gamewindowdata.h>
#include <graphics\components\modelcomponent.h>
#include <graphics\d3d\d3dcontext.h>
#include <graphics\model\vertexlist.h>
#include <graphics\shaders\shader.h>

namespace OK
{
    const bool GraphicsWrapper::K_FULL_SCREEN{ false };
    const bool GraphicsWrapper::K_VSYNC_ENABLED{ true };
    const float GraphicsWrapper::K_SCREEN_DEPTH{ 1000.0f };
    const float GraphicsWrapper::K_SCREEN_NEAR{ 0.1f };

    GraphicsWrapper::GraphicsWrapper()
        : m_D3DContext{ nullptr }
    {
    }

    EResult GraphicsWrapper::Init(const GameWindowData& windowData)
    {
        EResult result{ EResult::Success };

        m_D3DContext = new D3DContext;
        if (m_D3DContext)
        {
            if (!m_D3DContext->Initialize(windowData.m_WindowWidth, windowData.m_WindowHeight, K_VSYNC_ENABLED, windowData.m_WindowHandle, K_FULL_SCREEN, K_SCREEN_DEPTH, K_SCREEN_NEAR))
            {
                MessageBox(windowData.m_WindowHandle, "Could not initialize Direct3D", "Error", MB_OK);
                result = EResult::Failure;
            }
        }
        else
        {
            result = EResult::Failure;
        }

        m_D3DContext->ComputeRenderingContext(m_RenderingContext, nullptr);
        m_ShaderLibrary.PopulateLibrary(m_RenderingContext);

        return result;
    }

    void GraphicsWrapper::Shutdown()
    {
        m_ShaderLibrary.ClearLibrary();

        if (m_D3DContext != nullptr)
        {
            m_D3DContext->Shutdown();
            okSafeDelete(m_D3DContext);
        }
    }

    void GraphicsWrapper::BeginScene(const TransformComponent* cameraTransform)
    {
        m_D3DContext->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
        m_D3DContext->ComputeRenderingContext(m_RenderingContext, cameraTransform);
    }

    void GraphicsWrapper::EndScene()
    {
        m_D3DContext->EndScene();
    }

    EResult GraphicsWrapper::RegisterModels(JSONNode* modelListNode)
    {
        return m_ModelLibrary.RegisterModels(m_RenderingContext, modelListNode);
    }

    void GraphicsWrapper::RenderModel(const ModelComponent* model, const TransformComponent* transform)
    {
        VertexList* foundModel{ m_ModelLibrary.FindModel(model->GetModelName().begin()) };
        if (foundModel != nullptr)
        {
            m_D3DContext->PrepareModelRendering(m_RenderingContext, *foundModel, transform);
            Shader* foundShader{ m_ShaderLibrary.FindShader(model->GetShaderName().begin()) };
            if (foundShader != nullptr)
            {
                foundShader->RunShader(m_RenderingContext, foundModel->GetIndexCount());
            }
        }
    }
}