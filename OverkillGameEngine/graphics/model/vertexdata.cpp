#include <stdafx.h>
#include <graphics\model\vertexdata.h>

#include <malloc.h>

namespace OK
{
    void* VertexData::operator new(size_t size)
    {
        return _aligned_malloc(size, alignof(OK::Vec4));
    }

    void* VertexData::operator new[](size_t size)
    {
        return _aligned_malloc(size, alignof(OK::Vec4));
    }

    void VertexData::operator delete(void* pointer)
    {
        _aligned_free(pointer);
    }

    void VertexData::operator delete[](void* pointer)
    {
        _aligned_free(pointer);
    }
}