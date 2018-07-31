#pragma once

#include <core\containers\array.h>

namespace OK
{
    template<typename T>
    class PointerArray : public Array<T*>
    {
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