#pragma once

namespace OK
{
    template<typename T>
    class BaseStringView
    {
    public:
        BaseStringView(const T* stringStart, OK::u32 stringLength);

        void GetLength() const;

        using iterator = T*;
        using const_iterator = const T*;

        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;

    private:
        const T* m_StringStart;
        const T* m_StringEnd;
    };

    template<typename T>
    BaseStringView<T>::BaseStringView(const T* stringStart, OK::u32 stringLength)
        : m_StringStart{ stringStart }
        , m_StringEnd{ stringStart + stringLength }
    {
    }

    template<typename T>
    void BaseStringView<T>::GetLength() const
    {
        return (m_StrinEnd - m_StringStart) / sizeof(T);
    }

    template<typename T>
    BaseStringView<T>::iterator BaseStringView<T>::begin()
    {
        return m_StringStart;
    }

    template<typename T>
    BaseStringView<T>::const_iterator BaseStringView<T>::begin() const
    {
        return m_StringStart;
    }

    template<typename T>
    BaseStringView<T>::iterator BaseStringView<T>::end()
    {
        return m_StringEnd;
    }

    template<typename T>
    BaseStringView<T>::const_iterator BaseStringView<T>::end() const
    {
        return m_StringEnd;
    }
}