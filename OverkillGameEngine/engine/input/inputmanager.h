#pragma once

#include <core\singleton.h>
#include <engine\input\inputenums.h>

namespace OK
{
    struct GameWindowEventData;

    class InputManager : public Singleton<InputManager>
    {
    public:
        void Init();
        void Shutdown();
        void HandleWindowEvent(const GameWindowEventData& eventData);
    };
}