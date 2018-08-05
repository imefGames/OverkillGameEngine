#pragma once

namespace OK
{
    struct GameWindowData
    {
        HINSTANCE m_InstanceHandle = nullptr;
        HWND m_WindowHandle = nullptr;
        OK::s32 m_CommandCount = 0;

        OK::s32 m_WindowWidth = 0;
        OK::s32 m_WindowHeight = 0;
    };
}