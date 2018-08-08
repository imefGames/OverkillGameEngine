#include <stdafx.h>
#include <graphics\graphicssystem.h>

#include <engine\components\transformcomponent.h>
#include <engine\objectmodel\componentutils.h>
#include <graphics\camerasystem.h>
#include <graphics\graphicswrapper.h>
#include <graphics\components\modelcomponent.h>

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

        ComponentHolderID cameraHolderID{ CameraSystem::GetActiveCameraComponentHolderID() };
        TransformComponent* cameraTransform{ nullptr };
        ComponentUtils::FindComponents(cameraHolderID, cameraTransform);
        m_GraphicsWrapper->SetCameraTransform(cameraTransform);

        const Array<ComponentHolderID>& activeHolderIDs{ GetActiveComponentHolders() };
        for (ComponentHolderID holderID : activeHolderIDs)
        {
            ModelComponent* modelTransform{ nullptr };
            TransformComponent* currentTransform{ nullptr };
            if (ComponentUtils::FindComponents(cameraHolderID, modelTransform, currentTransform) == EResult::Success)
            {
                m_GraphicsWrapper->RenderModel(modelTransform, currentTransform);
            }
        }

        m_GraphicsWrapper->EndScene();
    }

}