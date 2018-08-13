#pragma once

namespace OK
{
    template <typename Policy>
    class AllocationPolicy
    {
    public:
        static void* operator new(size_t size);
        static void* operator new[](size_t size);
        static void operator delete(void* pointer);
        static void operator delete[](void* pointer);
    };

    template <typename Policy>
    void* AllocationPolicy<Policy>::operator new(size_t size)
    {
        return Policy::Allocate(size);
    }

    template <typename Policy>
    void* AllocationPolicy<Policy>::operator new[](size_t size)
    {
        return Policy::AllocateArray(size);
    }

    template <typename Policy>
    void AllocationPolicy<Policy>::operator delete(void* pointer)
    {
        Policy::Free(pointer);
    }

    template <typename Policy>
    void AllocationPolicy<Policy>::operator delete[](void* pointer)
    {
        Policy::FreeArray(pointer);
    }
}