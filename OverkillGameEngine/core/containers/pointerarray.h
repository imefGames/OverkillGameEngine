#pragma once

#include <core\containers\array.h>
#include <core\traits.h>

namespace OK
{
    template<typename T>
    class PointerArray : public Array<T>
    {
        static_assert(OK::IsPointer<T>::value, "Contained type must be a pointer");
    public:
        void DeleteAll();
    };

    template<typename T>
    void PointerArray<T>::DeleteAll()
    {
        for (T* currentPointer : *this)
        {
            delete currentPointer;
        }
        Clear();
    }
}