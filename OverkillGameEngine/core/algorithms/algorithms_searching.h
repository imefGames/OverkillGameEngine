#pragma once

namespace OK
{
    template<typename InIterator, typename SearchedItemType>
    InIterator Find(InIterator beginIt, InIterator endIt, const SearchedItemType& searchedItem)
    {
        InIterator foundIt = beginIt;
        while (foundIt != endIt && *foundIt != searchedItem)
        {
            ++foundIt;
        }
        return foundIt;
    }

    template<typename InIterator, typename UnaryPredicate>
    InIterator FindIf(InIterator beginIt, InIterator endIt, const UnaryPredicate& predicate)
    {
        InIterator foundIt = beginIt;
        while (foundIt != endIt && !predicate(*foundIt))
        {
            ++foundIt;
        }
        return foundIt;
    }
}