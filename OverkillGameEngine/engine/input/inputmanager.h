#pragma once

#include <core\singleton.h>
#include <core\math\vectors.h>
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
        static OK::Bool IsMouseButtonDown(EMouseButton buttonCode);
        static OK::u32 GetMouseX();
        static OK::u32 GetMouseY();

    private:
        static const OK::u32 K_KEY_STATE_ARRAY_SIZE = 256;

        Array<OK::Bool> m_KeyStates;
        Array<OK::Bool> m_MouseButtonStates;
        OK::u32 m_MousePositionX;
        OK::u32 m_MousePositionY;
    };
}