#include <stdafx.h>
#include <engine\gameengine.h>

#include <core\io\parsers\json\jsonnode.h>
#include <core\io\parsers\json\jsonparser.h>
#include <engine\gameloop.h>
#include <engine\input\inputmanager.h>
#include <engine\objectmodel\universe.h>
#include <engine\window\gamewindow.h>
#include <engine\window\gamewindoweventdata.h>
#include <graphics\graphicswrapper.h>
#include <ctime>

namespace OK
{
    const OK::char8* K_GAME_DATA_FILE_PATH = "GameData.json";

    void GameEngine::Init(GameWindowData& windowData)
    {
        ComponentHolder::CreateSingleton();
        GraphicsWrapper::CreateSingleton();
        InputManager::CreateSingleton();
        m_InputManager = InputManager::Get();
        m_GameLoop = new GameLoop;
        m_GameWindow = new GameWindow;

        m_GameLoop->Init();
        m_GameWindow->Init(windowData);
        GraphicsWrapper::Get()->Init(windowData);
        m_InputManager->Init();

        LoadGameData("GameData.json");
    }

    void GameEngine::Shutdown()
    {
        m_InputManager->Shutdown();
        GraphicsWrapper::Get()->Shutdown();

        m_GameWindow->Shutdown();
        m_GameLoop->Shutdown();

        okSafeDelete(m_GameLoop);
        okSafeDelete(m_GameWindow);
        m_InputManager = nullptr;
        InputManager::DeleteSingleton();
        GraphicsWrapper::DeleteSingleton();
        ComponentHolder::DeleteSingleton();
    }

    void GameEngine::RunEngineUntilEnd()
    {
        GameWindowEventData eventData;
        OK::f32 deltaTime{ 0.001f }; //TODO: compute delta time
        OK::Bool keepRunning{ true };
        while (keepRunning)
        {
            std::clock_t frameStart = std::clock();

            m_GameWindow->PollEvents(eventData);
            m_InputManager->HandleWindowEvent(eventData);
            m_GameLoop->Tick(eventData, deltaTime);

            std::clock_t frameEnd = std::clock();
            deltaTime = (static_cast<OK::f32>(frameEnd - frameStart) / CLOCKS_PER_SEC);

            if (eventData.m_QuitGame)
            {
                keepRunning = false;
            }
        }
    }

    void GameEngine::LoadGameData(const OK::char8* filePath)
    {
        EResult loadResult{ EResult::Failure };
        JSONParser parser{ filePath };
        if (parser.ParseRootNodes() == EResult::Success)
        {
            JSONNode* universeNode = parser.GetNode("Universe");
            loadResult = Universe::Get()->LoadGameData(universeNode);
        }

        if (loadResult == EResult::Failure)
        {
            //TODO: Show error message in message box.
        }
    }
}