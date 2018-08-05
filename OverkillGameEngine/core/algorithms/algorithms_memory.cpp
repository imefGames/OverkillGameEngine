#include <stdafx.h>
#include <core\algorithms\algorithms_memory.h>

#include <cstring>

namespace OK
{
    void MemCopy(void* source, void* destination, OK::u32 byteCount)
    {
        std::memcpy(source, destination, byteCount);
    }
}