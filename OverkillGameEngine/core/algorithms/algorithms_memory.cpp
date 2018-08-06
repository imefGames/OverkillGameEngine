#include <stdafx.h>
#include <core\algorithms\algorithms_memory.h>

#include <cstring>

namespace OK
{
    void MemCopy(const void* source, void* destination, OK::u32 byteCount)
    {
        std::memcpy(destination, source, byteCount);
    }

    OK::Bool MemEqual(const void* sourceA, const void* sourceB, OK::u32 byteCount)
    {
        const OK::char8* sourceAChar = reinterpret_cast<const OK::char8*>(sourceA);
        const OK::char8* sourceBChar = reinterpret_cast<const OK::char8*>(sourceB);
        for(OK::u32 i = 0; i < byteCount; ++i)
        {
            if (sourceAChar[i] != sourceAChar[i])
            {
                return false;
            }
        }
        return true;
    }
}