#pragma once

#include <iostream>
#include <windows.h>

#define okAssert(condition, errorMessage) \
    if (condition) {} else \
    { \
        std::cerr << errorMessage << std::endl; \
        DebugBreak(); \
    }