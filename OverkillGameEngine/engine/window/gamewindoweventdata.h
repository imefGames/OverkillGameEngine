#pragma once

#include <engine\input\inputenums.h>

namespace OK
{
    struct GameWindowEventData
    {
        OK::Bool m_QuitGame = false;
        EKeyboardMouseInputEvent m_KeyboardEvent = EKeyboardMouseInputEvent::None;
        EMouseButton m_MouseButtonCode = EMouseButton::None;
        OK::u32 m_KeyboardKeyCode = 0;
        OK::u32 m_MousePositionX{ 0 };
        OK::u32 m_MousePositionY{ 0 };
    };
}