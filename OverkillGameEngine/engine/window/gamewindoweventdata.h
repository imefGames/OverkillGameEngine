#pragma once

#include <engine\input\inputenums.h>

namespace OK
{
    struct GameWindowEventData
    {
        OK::Bool m_QuitGame = false;
        EKeyboardInputEvent m_KeyboardEvent = EKeyboardInputEvent::None;
        OK::u32 m_KeyboardKeyCode = 0;
    };
}