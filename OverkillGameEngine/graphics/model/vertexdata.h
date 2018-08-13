#pragma once

#include <core\math\vectors.h>

namespace OK
{
    struct alignas(alignof(OK::Vec4)) VertexData : public AllocationPolicy<AlignedAllocation<alignof(OK::Vec4)>>
    {
        OK::Vec4 m_Position;
        OK::Vec4 m_Color;
        OK::Vec4 m_TextureCoords;
        OK::Vec4 m_Normal;
    };
}