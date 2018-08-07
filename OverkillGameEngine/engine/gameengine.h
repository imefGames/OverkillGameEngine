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
        void LoadGameData(const OK::char8* filePath);

        static const OK::char8* K_GAME_DATA_FILE_PATH;

        GameLoop* m_GameLoop;
        GameWindow* m_GameWindow;
    };
}