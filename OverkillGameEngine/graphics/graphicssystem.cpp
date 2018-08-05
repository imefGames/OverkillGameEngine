#include <stdafx.h>
#include <graphics\graphicssystem.h>

#include <graphics\graphicswrapper.h>

namespace OK
{
    GraphicsSystem::GraphicsSystem()
        : m_GraphicsWrapper{ nullptr }
    {
    }

    void GraphicsSystem::Init()
    {
        m_GraphicsWrapper = GraphicsWrapper::Get();
    }

    void GraphicsSystem::Shutdown()
    {
        m_GraphicsWrapper = nullptr;
    }

    void GraphicsSystem::Update(OK::f32 dt)
    {
        m_GraphicsWrapper->BeginScene();
        m_GraphicsWrapper->EndScene();
    }

}