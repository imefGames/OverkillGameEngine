#include <stdafx.h>
#include <core\algorithms\algorithms_memory.h>

#include <cstring>

namespace OK
{
    void MemCopy(const void* source, void* destination, OK::u32 byteCount)
    {
        std::memcpy(destination, source, byteCount);
    }
}