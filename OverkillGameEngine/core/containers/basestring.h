#pragma once

#include <core\containers\array.h>

namespace OK
{
    template<typename T>
    class BaseString : public Array<T>
    {
    public:
        BaseString();
        BaseString(const T* beginString, OK::u32 stringLength);
        BaseString(const T* rawString);
    };

    template<typename T>
    BaseString<T>::BaseString()
        : Array<T>{ }
    {
    }

    template<typename T>
    BaseString<T>::BaseString(const T* beginString, OK::u32 stringLength)
    {
        Reserve(stringLength + 1); //+1 to include '\0'
        Resize(stringLength);
        OK::MemCopy(reinterpret_cast<const void*>(beginString), GetRawData(), stringLength * sizeof(T));
        GetRawData()[stringLength] = 0;
    }

    template<typename T>
    BaseString<T>::BaseString(const T* rawString)
    {
        OK::u32 stringLength = 0;
        const T* currentChar = rawString;
        while (*currentChar != 0)
        {
            ++currentChar;
            ++stringLength;
        }
        Reserve(stringLength + 1); //+1 to include '\0'
        Resize(stringLength);
        OK::MemCopy(reinterpret_cast<const void*>(rawString), GetRawData(), stringLength * sizeof(T));
        GetRawData()[stringLength] = 0;
    }
}