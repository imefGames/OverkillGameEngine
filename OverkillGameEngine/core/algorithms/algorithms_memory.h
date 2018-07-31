#pragma once

#include <core\types.h>

namespace OK
{
    void MemCopy(void* source, void* destination, OK::u32 byteCount);

    template<typename ContainerType, typename PointerType>
    PointerType* Begin(ContainerType& container)
    {
        return container.begin();
    }

    template<typename ContainerType, typename PointerType>
    const PointerType* Begin(const ContainerType& container)
    {
        return container.begin();
    }

    template<typename PointerType, OK::u32 ArraySize>
    PointerType* Begin(PointerType container[ArraySize])
    {
        return container;
    }

    template<typename PointerType, OK::u32 ArraySize>
    const PointerType* Begin(const PointerType container[ArraySize])
    {
        return container;
    }

    template<typename ContainerType, typename PointerType>
    PointerType* End(ContainerType& container)
    {
        return container.end();
    }

    template<typename ContainerType, typename PointerType>
    const PointerType* End(const ContainerType& container)
    {
        return container.end();
    }

    template<typename PointerType, OK::u32 ArraySize>
    PointerType* End(PointerType container[ArraySize])
    {
        return container + ArraySize;
    }

    template<typename PointerType, OK::u32 ArraySize>
    const PointerType* End(const PointerType container[ArraySize])
    {
        return container + ArraySize;
    }
}