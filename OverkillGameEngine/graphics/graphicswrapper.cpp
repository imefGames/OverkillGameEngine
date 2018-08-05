#include <stdafx.h>
#include <graphics\graphicswrapper.h>

#include <engine\window\gamewindowdata.h>
#include <graphics\d3d\d3dcontext.h>

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

        return result;
    }

    void GraphicsWrapper::Shutdown()
    {
        if (m_D3DContext != nullptr)
        {
            m_D3DContext->Shutdown();
            okSafeDelete(m_D3DContext);
        }
    }

    void GraphicsWrapper::BeginScene()
    {
        m_D3DContext->BeginScene(0.5f, 0.5f, 0.5f, 1.0f);
    }

    void GraphicsWrapper::EndScene()
    {
        m_D3DContext->EndScene();
    }
}