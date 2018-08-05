#include <stdafx.h>

#include <tchar.h>
#include <windows.h>

//TODO: move elsewhere once rendering pipe is done.
constexpr OK::u32 K_WINDOW_WIDTH = 640;
constexpr OK::u32 K_WINDOW_HEIGHT = 480;

constexpr OK::u32 K_MAIN_ERROR_RETURN_VALUE = 1;

HINSTANCE g_Instance_Handle;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(HINSTANCE instanceHandle, HINSTANCE previousInstanceHandle, LPSTR commandLine, int commandCount)
{
    TCHAR szWindowClass[] = _T("win32app");
    TCHAR szTitle[] = _T("Win32 Guided Tour Application");

    WNDCLASSEX windowsClassData;
    windowsClassData.cbSize = sizeof(WNDCLASSEX);
    windowsClassData.style = CS_HREDRAW | CS_VREDRAW;
    windowsClassData.lpfnWndProc = WndProc;
    windowsClassData.cbClsExtra = 0;
    windowsClassData.cbWndExtra = 0;
    windowsClassData.hInstance = instanceHandle;
    windowsClassData.hIcon = LoadIcon(instanceHandle, IDI_APPLICATION);
    windowsClassData.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowsClassData.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    windowsClassData.lpszMenuName = NULL;
    windowsClassData.lpszClassName = szWindowClass;
    windowsClassData.hIconSm = LoadIcon(windowsClassData.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&windowsClassData))
    {
        MessageBox(NULL, _T("Call to RegisterClassEx failed!"), _T("Win32 Guided Tour"), NULL);
        return K_MAIN_ERROR_RETURN_VALUE;
    }

    g_Instance_Handle = instanceHandle;
    HWND windowHandle = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, K_WINDOW_WIDTH, K_WINDOW_HEIGHT, NULL, NULL, instanceHandle, NULL);
    if (!windowHandle)
    {
        MessageBox(NULL, _T("Call to CreateWindow failed!"), _T("Win32 Guided Tour"), NULL);
        return K_MAIN_ERROR_RETURN_VALUE;
    }

    ShowWindow(windowHandle, commandCount);
    UpdateWindow(windowHandle);

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
    return static_cast<OK::s32>(message.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT returnValue{};
    switch (message)
    {
        case WM_PAINT:
        {
            break;
        }

        case WM_DESTROY:
        {
            PostQuitMessage(0);
            break;
        }

        default:
        {
            returnValue = DefWindowProc(hWnd, message, wParam, lParam);
            break;
        }
    }

    return returnValue;
}