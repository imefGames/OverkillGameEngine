#pragma once

namespace OK
{
    class GameLoop;
    class GameWindow;
    struct GameWindowData;

    class GameEngine
    {
    public:
        void Init(GameWindowData& windowData);
        void Shutdown();
        void RunEngineUntilEnd();
    private:
        GameLoop* m_GameLoop;
        GameWindow* m_GameWindow;
    };
}