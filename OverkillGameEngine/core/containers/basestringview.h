#pragma once

namespace OK
{
    template<typename T>
    class BaseStringView
    {
    public:
        BaseStringView();
        BaseStringView(T* stringStart, OK::u32 stringLength);

        OK::u32 GetLength() const;

        using iterator = T*;
        using const_iterator = const T*;

        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;

        OK::Bool operator==(const T* lhs);
        OK::Bool operator!=(const T* lhs);

    private:
        T* m_StringStart;
        T* m_StringEnd;
    };

    template<typename T>
    BaseStringView<T>::BaseStringView()
        : m_StringStart{ nullptr }
        , m_StringEnd{ nullptr }
    {
    }

    template<typename T>
    BaseStringView<T>::BaseStringView(T* stringStart, OK::u32 stringLength)
        : m_StringStart{ stringStart }
        , m_StringEnd{ stringStart + stringLength }
    {
    }

    template<typename T>
    OK::u32 BaseStringView<T>::GetLength() const
    {
        return (m_StringEnd - m_StringStart) / sizeof(T);
    }

    template<typename T>
    typename BaseStringView<T>::iterator BaseStringView<T>::begin()
    {
        return m_StringStart;
    }

    template<typename T>
    typename BaseStringView<T>::const_iterator BaseStringView<T>::begin() const
    {
        return m_StringStart;
    }

    template<typename T>
    typename BaseStringView<T>::iterator BaseStringView<T>::end()
    {
        return m_StringEnd;
    }

    template<typename T>
    typename BaseStringView<T>::const_iterator BaseStringView<T>::end() const
    {
        return m_StringEnd;
    }

    template<typename T>
    OK::Bool BaseStringView<T>::operator==(const T* lhs)
    {
        return MemEqual(m_StringStart, lhs, GetLength());
    }

    template<typename T>
    OK::Bool BaseStringView<T>::operator!=(const T* lhs)
    {
        return !(*this == lhs);
    }
}