#pragma once

namespace OK
{
    struct GameWindowData;
    struct GameWindowEventData;

    class GameWindow
    {
    public:
        EResult Init(const GameWindowData& windowData);
        void Shutdown();
        void PollEvents(GameWindowEventData& eventData);

    private:
        //TODO: move elsewhere once rendering pipe is done.
        static const OK::u32 K_WINDOW_WIDTH;
        static const OK::u32 K_WINDOW_HEIGHT;

        HINSTANCE m_InstanceHandle;
    };
}