#pragma once

#include <core\types.h>
#include <malloc.h>

namespace OK
{
    template <OK::u32 Alignment>
    class AlignedAllocation
    {
    public:
        static void* Allocate(size_t size);
        static void* AllocateArray(size_t size);
        static void Free(void* pointer);
        static void FreeArray(void* pointer);
    };

    template <OK::u32 Alignment>
    void* AlignedAllocation<Alignment>::Allocate(size_t size)
    {
        return _aligned_malloc(size, Alignment);
    }

    template <OK::u32 Alignment>
    void* AlignedAllocation<Alignment>::AllocateArray(size_t size)
    {
        return _aligned_malloc(size, Alignment);
    }

    template <OK::u32 Alignment>
    void AlignedAllocation<Alignment>::Free(void* pointer)
    {
        _aligned_free(pointer);
    }

    template <OK::u32 Alignment>
    void AlignedAllocation<Alignment>::FreeArray(void* pointer)
    {
        _aligned_free(pointer);
    }
}