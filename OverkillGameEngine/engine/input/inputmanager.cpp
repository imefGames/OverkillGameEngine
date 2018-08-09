#include <stdafx.h>
#include <engine\input\inputmanager.h>

#include <engine\window\gamewindoweventdata.h>

namespace OK
{
    void InputManager::Init()
    {
        m_KeyStates.Resize(K_KEY_STATE_ARRAY_SIZE);
        for (OK::Bool& currentKey : m_KeyStates)
        {
            currentKey = false;
        }
    }

    void InputManager::Shutdown()
    {
        m_KeyStates.Clear();
    }

    void InputManager::HandleWindowEvent(const GameWindowEventData& eventData)
    {
        switch (eventData.m_KeyboardEvent)
        {
            case EKeyboardInputEvent::KeyDown:
            {
                m_KeyStates[eventData.m_KeyboardKeyCode] = true;
                break;
            }

            case EKeyboardInputEvent::KeyUp:
            {
                m_KeyStates[eventData.m_KeyboardKeyCode] = false;
                break;
            }
        }
    }

    OK::Bool InputManager::IsKeyDown(EKeyboardKey keyCode)
    {
        return InputManager::Get()->m_KeyStates[static_cast<OK::u32>(keyCode)];
    }
}