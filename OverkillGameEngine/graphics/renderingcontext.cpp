#include <stdafx.h>
#include <graphics\renderingcontext.h>

namespace OK
{
    void* RenderingContext::operator new(size_t size)
    {
        return _aligned_malloc(size, alignof(OK::Vec4));
    }

    void* RenderingContext::operator new[](size_t size)
    {
        return _aligned_malloc(size, alignof(OK::Vec4));
    }

        void RenderingContext::operator delete(void* pointer)
    {
        _aligned_free(pointer);
    }

    void RenderingContext::operator delete[](void* pointer)
    {
        _aligned_free(pointer);
    }
}