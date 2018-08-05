#pragma once

namespace OK
{
    class Universe;
    struct GameWindowEventData;

    class GameLoop
    {
    public:
        void Init();
        void Shutdown();
        void Tick(const GameWindowEventData& eventData, OK::f32 dt);

    private:
        Universe* m_Universe;
    };
}