#pragma once

#include <core\types.h>

namespace OK
{
    template<typename InIterator, typename OutIterator, typename SearchedItemType>
    OutIterator Find(InIterator beginIt, InIterator endIt, const SearchedItemType& searchedItem)
    {
        OutIterator foundIt = beginIt;
        while (foundIt != endIt && *foundIt != searchedItem)
        {
            ++foundIt;
        }
        return foundIt;
    }
}