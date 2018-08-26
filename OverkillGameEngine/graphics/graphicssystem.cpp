#include <stdafx.h>
#include <graphics\graphicssystem.h>

#include <engine\components\recttransformcomponent.h>
#include <engine\components\transformcomponent.h>
#include <engine\objectmodel\componentutils.h>
#include <graphics\subsystems\camerasubsystem.h>
#include <graphics\subsystems\lightsubsystem.h>
#include <graphics\graphicswrapper.h>
#include <graphics\components\lightsourcecomponent.h>
#include <graphics\components\modelcomponent.h>
#include <graphics\components\spritecomponent.h>

namespace OK
{
    GraphicsSystem::GraphicsSystem()
        : m_GraphicsWrapper{ nullptr }
    {
    }

    void GraphicsSystem::Init()
    {
        UniverseSystem::Init();

        m_GraphicsWrapper = GraphicsWrapper::Get();

        RegisterSubSystem<CameraSubSystem>();
        RegisterSubSystem<LightSubSystem>();
    }

    void GraphicsSystem::Shutdown()
    {
        m_GraphicsWrapper = nullptr;

        UniverseSystem::Shutdown();
    }

    void GraphicsSystem::Update(OK::f32 dt)
    {
        UniverseSystem::Update(dt);

        ComponentHolderID cameraHolderID{ CameraSubSystem::GetActiveCameraComponentHolderID() };
        TransformComponent* cameraTransform{ nullptr };
        ComponentUtils::FindComponents(cameraHolderID, cameraTransform);
        m_GraphicsWrapper->BeginScene(cameraTransform);

        ComponentHolderID lightHolderID{ LightSubSystem::GetActiveLightomponentHolderID() };
        LightSourceComponent* lightComponent{ nullptr };
        TransformComponent* lightTransform{ nullptr };
        if (ComponentUtils::FindComponents(lightHolderID, lightComponent, lightTransform) == EResult::Success)
        {
            m_GraphicsWrapper->SetLight(lightComponent, lightTransform);
        }

        //3D Model pass
        const Array<ComponentHolderID>& activeHolderIDs{ GetActiveComponentHolders() };
        for (ComponentHolderID holderID : activeHolderIDs)
        {
            ModelComponent* model{ nullptr };
            TransformComponent* transform{ nullptr };
            if (ComponentUtils::FindComponents(holderID, model, transform) == EResult::Success)
            {
                m_GraphicsWrapper->RenderModel(model, transform);
            }
        }

        //2D Model pass
        m_GraphicsWrapper->Begin2DRenderingPass();
        for (ComponentHolderID holderID : activeHolderIDs)
        {
            SpriteComponent* sprite{ nullptr };
            RectTransformComponent* transform{ nullptr };
            if (ComponentUtils::FindComponents(holderID, sprite, transform) == EResult::Success)
            {
                m_GraphicsWrapper->RenderSprite(sprite, transform);
            }
        }
        m_GraphicsWrapper->End2DRenderingPass();

        m_GraphicsWrapper->EndScene();
    }

}