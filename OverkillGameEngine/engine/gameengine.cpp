#include <stdafx.h>
#include <engine\gameengine.h>

#include <engine\gameloop.h>
#include <engine\window\gamewindow.h>
#include <engine\window\gamewindoweventdata.h>

namespace OK
{
    void GameEngine::Init(const GameWindowData& windowData)
    {
        m_GameLoop = new GameLoop;
        m_GameWindow = new GameWindow;

        m_GameLoop->Init();
        m_GameWindow->Init(windowData);
    }

    void GameEngine::Shutdown()
    {
        m_GameWindow->Shutdown();
        m_GameLoop->Shutdown();

        okSafeDelete(m_GameLoop);
        okSafeDelete(m_GameWindow);
    }

    void GameEngine::RunEngineUntilEnd()
    {
        GameWindowEventData eventData;
        OK::f32 deltaTime{ 0.0f }; //TODO: compute delta time
        OK::Bool keepRunning{ true };
        while (keepRunning)
        {
            m_GameWindow->PollEvents(eventData);
            m_GameLoop->Tick(eventData, deltaTime);
            keepRunning = false;
        }
    }
}