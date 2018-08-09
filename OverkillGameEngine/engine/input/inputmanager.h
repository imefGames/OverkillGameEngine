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

        static OK::Bool IsKeyDown(EKeyboardKey keyCode);

    private:
        static const OK::u32 K_KEY_STATE_ARRAY_SIZE = 256;

        Array<OK::Bool> m_KeyStates;
    };
}