#include <stdafx.h>
#include <engine\window\gamewindow.h>

#include <tchar.h>
#include <windows.h>
#include <engine\window\gamewindowdata.h>

namespace OK
{
    LRESULT CALLBACK WndProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);

    const OK::u32 GameWindow::K_WINDOW_WIDTH = 640;
    const OK::u32 GameWindow::K_WINDOW_HEIGHT = 480;

    EResult GameWindow::Init(const GameWindowData& windowData)
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
            HWND windowHandle = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, K_WINDOW_WIDTH, K_WINDOW_HEIGHT, NULL, NULL, windowData.m_InstanceHandle, NULL);
            if (windowHandle)
            {
                ShowWindow(windowHandle, windowData.m_CommandCount);
                UpdateWindow(windowHandle);
            }
            else
            {
                MessageBox(NULL, _T("Call to CreateWindow failed!"), _T("Win32 Guided Tour"), NULL);
                return EResult::Failure;
            }
        }
        else
        {
            MessageBox(NULL, _T("Call to RegisterClassEx failed!"), _T("Win32 Guided Tour"), NULL);
            initResult = EResult::Failure;
        }
        return initResult;
    }

    void GameWindow::Shutdown()
    {
    }

    void GameWindow::PollEvents(GameWindowEventData& eventData)
    {
        //TODO: fill eventData

        MSG message;
        BOOL messageReturnVal;
        while ((messageReturnVal = GetMessage(&message, NULL, 0, 0)) != 0)
        {
            if (messageReturnVal == -1)
            {
                // handle the error and possibly exit
                break;
            }
            else
            {
                TranslateMessage(&message);
                DispatchMessage(&message);
            }
        }
    }

    LRESULT CALLBACK WndProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
    {
        LRESULT returnValue{};
        switch (message)
        {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
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