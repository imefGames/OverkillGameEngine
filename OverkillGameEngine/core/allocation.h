#pragma once

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