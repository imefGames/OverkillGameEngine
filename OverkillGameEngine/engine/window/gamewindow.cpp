#include <stdafx.h>
#include <engine\window\gamewindow.h>

#include <tchar.h>
#include <windows.h>
#include <engine\window\gamewindowdata.h>
#include <engine\window\gamewindoweventdata.h>

namespace OK
{
    OK::Bool g_PressedQuit{ false };
    EKeyboardMouseInputEvent g_KeyboardEvent{ EKeyboardMouseInputEvent::None };
    EMouseButton g_MouseButtonCode{ EMouseButton::None };
    OK::u32 g_KeyboardKeyCode{ 0 };
    OK::u32 g_MousePositionX{ 0 };
    OK::u32 g_MousePositionY{ 0 };

    LRESULT CALLBACK WndProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);

    const OK::u32 GameWindow::K_WINDOW_WIDTH = 640;
    const OK::u32 GameWindow::K_WINDOW_HEIGHT = 480;

    EResult GameWindow::Init(GameWindowData& windowData)
    {
        EResult initResult{ EResult::Success };

        TCHAR szWindowClass[] = _T("Overkill");
        TCHAR szTitle[] = _T("Overkill");

        WNDCLASSEX windowsClassData;
        windowsClassData.cbSize = sizeof(WNDCLASSEX);
        windowsClassData.style = CS_HREDRAW | CS_VREDRAW;
        windowsClassData.lpfnWndProc = WndProc;
        windowsClassData.cbClsExtra = 0;
        windowsClassData.cbWndExtra = 0;
        windowsClassData.hInstance = windowData.m_InstanceHandle;
        windowsClassData.hIcon = LoadIcon(windowData.m_InstanceHandle, IDI_APPLICATION);
        windowsClassData.hCursor = LoadCursor(NULL, IDC_ARROW);
        windowsClassData.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        windowsClassData.lpszMenuName = NULL;
        windowsClassData.lpszClassName = szWindowClass;
        windowsClassData.hIconSm = LoadIcon(windowsClassData.hInstance, IDI_APPLICATION);

        if (RegisterClassEx(&windowsClassData))
        {
            m_InstanceHandle = windowData.m_InstanceHandle;
            windowData.m_WindowHandle = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, K_WINDOW_WIDTH, K_WINDOW_HEIGHT, NULL, NULL, windowData.m_InstanceHandle, NULL);
            windowData.m_WindowWidth = K_WINDOW_WIDTH;
            windowData.m_WindowHeight = K_WINDOW_HEIGHT;
            if (windowData.m_WindowHandle)
            {
                ShowWindow(windowData.m_WindowHandle, windowData.m_CommandCount);
                UpdateWindow(windowData.m_WindowHandle);
            }
            else
            {
                MessageBox(NULL, _T("Call to CreateWindow failed!"), _T("Error"), NULL);
                return EResult::Failure;
            }
        }
        else
        {
            MessageBox(NULL, _T("Call to RegisterClassEx failed!"), _T("Error"), NULL);
            initResult = EResult::Failure;
        }
        return initResult;
    }

    void GameWindow::Shutdown()
    {
    }

    void GameWindow::PollEvents(GameWindowEventData& eventData)
    {
        g_KeyboardEvent = EKeyboardMouseInputEvent::None;
        g_MouseButtonCode = EMouseButton::None;
        g_KeyboardKeyCode = 0;
        g_PressedQuit = false;

        MSG message;
        if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }

        eventData.m_QuitGame = g_PressedQuit;
        eventData.m_KeyboardEvent = g_KeyboardEvent;
        eventData.m_KeyboardKeyCode = g_KeyboardKeyCode;
        eventData.m_MouseButtonCode = g_MouseButtonCode;
        eventData.m_MousePositionX = g_MousePositionX;
        eventData.m_MousePositionY = g_MousePositionY;
    }

    LRESULT CALLBACK WndProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
    {
        LRESULT returnValue{};
        switch (message)
        {
            case WM_KEYDOWN:
            {
                g_KeyboardEvent = EKeyboardMouseInputEvent::KeyDown;
                g_KeyboardKeyCode = static_cast<OK::u32>(wParam);
                break;
            }

            case WM_KEYUP:
            {
                g_KeyboardEvent = EKeyboardMouseInputEvent::KeyUp;
                g_KeyboardKeyCode = static_cast<OK::u32>(wParam);
                break;
            }

            case WM_LBUTTONDOWN:
            {
                g_KeyboardEvent = EKeyboardMouseInputEvent::MouseButtonDown;
                g_MouseButtonCode = EMouseButton::LeftButton;
                break;
            }

            case WM_LBUTTONUP:
            {
                g_KeyboardEvent = EKeyboardMouseInputEvent::MouseButtonUp;
                g_MouseButtonCode = EMouseButton::LeftButton;
                break;
            }

            case WM_RBUTTONDOWN:
            {
                g_KeyboardEvent = EKeyboardMouseInputEvent::MouseButtonDown;
                g_MouseButtonCode = EMouseButton::RightButton;
                break;
            }

            case WM_RBUTTONUP:
            {
                g_KeyboardEvent = EKeyboardMouseInputEvent::MouseButtonUp;
                g_MouseButtonCode = EMouseButton::RightButton;
                break;
            }

            case WM_MBUTTONDOWN:
            {
                g_KeyboardEvent = EKeyboardMouseInputEvent::MouseButtonDown;
                g_MouseButtonCode = EMouseButton::MiddleButton;
                break;
            }

            case WM_MBUTTONUP:
            {
                g_KeyboardEvent = EKeyboardMouseInputEvent::MouseButtonUp;
                g_MouseButtonCode = EMouseButton::MiddleButton;
                break;
            }

            case WM_MOUSEMOVE:
            {
                POINTS mousePosition = MAKEPOINTS(lParam);
                g_MousePositionX = static_cast<OK::u32>(mousePosition.x);
                g_MousePositionY = static_cast<OK::u32>(mousePosition.y);
                break;
            }

            case WM_DESTROY:
            {
                PostQuitMessage(0);
                g_PressedQuit = true;
                break;
            }

            default:
            {
                returnValue = DefWindowProc(windowHandle, message, wParam, lParam);
                break;
            }
        }

        return returnValue;
    }
}