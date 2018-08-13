#pragma once

namespace OK
{
    struct VertexData;

    class ModelLoaderObj
    {
    public:
        static EResult LoadModel(const StringView& path, Array<VertexData>& vertexData, Array<OK::u32>& indexData);
    };
}