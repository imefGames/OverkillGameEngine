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

        m_MouseButtonStates.Resize(static_cast<OK::u32>(EMouseButton::Count));
        for (OK::Bool& currentButton : m_MouseButtonStates)
        {
            currentButton = false;
        }
    }

    void InputManager::Shutdown()
    {
        m_KeyStates.Clear();
    }

    void InputManager::HandleWindowEvent(const GameWindowEventData& eventData)
    {
        m_MousePositionX = eventData.m_MousePositionX;
        m_MousePositionY = eventData.m_MousePositionY;

        switch (eventData.m_KeyboardEvent)
        {
            case EKeyboardMouseInputEvent::KeyDown:
            {
                m_KeyStates[eventData.m_KeyboardKeyCode] = true;
                break;
            }

            case EKeyboardMouseInputEvent::KeyUp:
            {
                m_KeyStates[eventData.m_KeyboardKeyCode] = false;
                break;
            }

            case EKeyboardMouseInputEvent::MouseButtonDown:
            {
                m_MouseButtonStates[static_cast<OK::u32>(eventData.m_MouseButtonCode)] = true;
                break;
            }

            case EKeyboardMouseInputEvent::MouseButtonUp:
            {
                m_MouseButtonStates[static_cast<OK::u32>(eventData.m_MouseButtonCode)] = false;
                break;
            }
        }
    }

    OK::Bool InputManager::IsKeyDown(EKeyboardKey keyCode)
    {
        return InputManager::Get()->m_KeyStates[static_cast<OK::u32>(keyCode)];
    }

    OK::Bool InputManager::IsMouseButtonDown(EMouseButton buttonCode)
    {
        return InputManager::Get()->m_MouseButtonStates[static_cast<OK::u32>(buttonCode)];
    }

    OK::u32 InputManager::GetMouseX()
    {
        return InputManager::Get()->m_MousePositionX;
    }

    OK::u32 InputManager::GetMouseY()
    {
        return InputManager::Get()->m_MousePositionY;
    }
}