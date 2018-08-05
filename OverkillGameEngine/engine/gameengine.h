#pragma once

namespace OK
{
    class GameLoop;
    class GameWindow;
    struct GameWindowData;

    class GameEngine
    {
    public:
        void Init(const GameWindowData& windowData);
        void Shutdown();
        void RunEngineUntilEnd();
    private:
        GameLoop* m_GameLoop;
        GameWindow* m_GameWindow;
    };
}