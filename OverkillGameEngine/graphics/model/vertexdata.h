#pragma once

#include <core\math\vectors.h>

namespace OK
{
    struct alignas(16) VertexData
    {
        OK::Vec4 m_Position;
        OK::Vec4 m_Color;

        static void* operator new(size_t size);
        static void* operator new[](size_t size);
        static void operator delete(void* pointer);
        static void operator delete[](void* pointer);
    };
}