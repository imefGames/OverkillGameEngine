#pragma once

#include <core\containers\basecontainer.h>

namespace OK
{
    template<typename T>
    class Array : public BaseContainer<T>
    {
    public:
        T& Add(const T& newElement);
        T& Insert(T&& newElement, OK::u32 elementIndex);
        T& Grow();
        void RemoveAt(OK::u32 elementIndex);
        void Remove(const T& removedElement);

        using iterator = T*;
        using const_iterator = const T*;

        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;
    };

    template<typename T>
    T& Array<T>::Add(const T& newElement)
    {
        T& addedElement = Grow();
        addedElement = newElement;
        return addedElement;
    }

    template<typename T>
    T& Array<T>::Insert(T&& newElement, OK::u32 elementIndex)
    {
        okAssert(elementIndex <= m_Size, "Invalid index: Can't insert outside of array.");
        if (m_Size >= m_MaxSize)
        {
            OK::u32 newSize = m_Size * 2;
            if (newSize == 0)
            {
                newSize = 4;
            }
            Reserve(newSize);
        }
        iterator insertIterator = begin() + elementIndex;
        OK::MemCopy(insertIterator, insertIterator + 1, m_Size - elementIndex);
        *lastIterator = std::forward<T>(newElement);
        ++m_Size;
        return *lastIterator;
    }

    template<typename T>
    T& Array<T>::Grow()
    {
        if (m_Size >= m_MaxSize)
        {
            OK::u32 newSize = m_Size * 2;
            if (newSize == 0)
            {
                newSize = 4;
            }
            Reserve(newSize);
        }
        iterator lastIterator = end();
        ++m_Size;
        return *lastIterator;
    }


    template<typename T>
    void Array<T>::RemoveAt(OK::u32 elementIndex)
    {
        okAssert(elementIndex <= m_Size, "Invalid index: Can't remove outside of array.");
        iterator removeIterator = begin() + elementIndex;
        for (iterator it = end() - 1; it > removeIterator; --it)
        {
            *(it - 1) = *it;
        }
        --m_Size;
    }

    template<typename T>
    void Array<T>::Remove(const T& removedElement)
    {
        const_iterator foundIterator = OK:Find(newElement);
        if (foundIterator != end())
        {
            RemoveAt(foundIterator - begin());
        }
    }

    template<typename T>
    typename Array<T>::iterator Array<T>::begin()
    {
        return GetRawData();
    }

    template<typename T>
    typename Array<T>::const_iterator Array<T>::begin() const
    {
        return GetRawData();
    }

    template<typename T>
    typename Array<T>::iterator Array<T>::end()
    {
        return GetRawData() + m_Size;
    }

    template<typename T>
    typename Array<T>::const_iterator Array<T>::end() const
    {
        return GetRawData() + m_Size;
    }
}