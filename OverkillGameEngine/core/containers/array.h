#include <core\asserts.h>
#include <core\containers\basecontainer.h>

namespace OK
{
    template<typename T>
    class Array : public BaseContainer<T>
    {
    public:
        void Add(T&& newElement);
        void Insert(T&& newElement, OK::u32 elementIndex);
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
    void Array<T>::Add(T&& newElement)
    {
        if (m_Size >= m_MaxSize)
        {
            Reserve(m_Size * 2);
        }
        iterator lastIterator = end();
        *lastIterator = std::forward<T>(newElement);
        ++m_Size;
    }

    template<typename T>
    void Array<T>::Insert(T&& newElement, OK::u32 elementIndex)
    {
        okAssert(elementIndex <= m_Size, "Invalid index: Can't insert outside of array.");
        if (m_Size >= m_MaxSize)
        {
            Reserve(m_Size * 2);
        }
        iterator insertIterator = begin() + elementIndex;
        OK::MemCopy(insertIterator, insertIterator + 1, m_Size - elementIndex);
        *lastIterator = std::forward<T>(newElement);
        ++m_Size;
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
    Array<T>::iterator Array<T>::begin()
    {
        return GetRawData();
    }

    template<typename T>
    Array<T>::const_iterator Array<T>::begin() const
    {
        return GetRawData();
    }

    template<typename T>
    Array<T>::iterator Array<T>::end()
    {
        return GetRawData() + m_Size;
    }

    template<typename T>
    Array<T>::const_iterator Array<T>::end() const
    {
        return GetRawData() + m_Size;
    }
}