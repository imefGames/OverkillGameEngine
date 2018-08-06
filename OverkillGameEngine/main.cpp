#include <stdafx.h>

#include <engine\gameengine.h>
#include <engine\window\gamewindowdata.h>

#include <core\io\parsers\json\jsonparser.h>
#include <core\io\parsers\json\jsonnode.h>

int CALLBACK WinMain(HINSTANCE instanceHandle, HINSTANCE previousInstanceHandle, LPSTR commandLine, OK::s32 commandCount)
{
    OK::GameWindowData windowData;
    windowData.m_InstanceHandle = instanceHandle;
    windowData.m_CommandCount = commandCount;

    OK::GameEngine gameEngine;
    gameEngine.Init(windowData);
    gameEngine.RunEngineUntilEnd();
    gameEngine.Shutdown();

    return 0;
}