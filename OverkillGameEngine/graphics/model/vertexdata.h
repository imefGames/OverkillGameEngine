#pragma once

#include <core\math\vectors.h>

namespace OK
{
    struct alignas(alignof(OK::Vec4)) VertexData : public AllocationPolicy<AlignedAllocation<alignof(OK::Vec4)>>
    {
        VertexData() = default;
        VertexData(const OK::Vec4& position, const OK::Vec4& color, const OK::Vec4& textureCoords, const OK::Vec4& normal)
            : m_Position{ position }
            , m_Color{ color }
            , m_TextureCoords{ textureCoords }
            , m_Normal{ normal }
        {
        }

        OK::Vec4 m_Position;
        OK::Vec4 m_Color;
        OK::Vec4 m_TextureCoords;
        OK::Vec4 m_Normal;
    };
}