#pragma once

#include <core\allocation\allocationpolicy.h>
#include <core\allocation\alignedallocation.h>

#define okSafeDelete(pointer) \
if (pointer == nullptr) {} else \
{ \
    delete pointer; \
    pointer = nullptr; \
}

#define okSafeDeleteArray(pointer) \
if (pointer == nullptr) {} else \
{ \
    delete[] pointer; \
    pointer = nullptr; \
}