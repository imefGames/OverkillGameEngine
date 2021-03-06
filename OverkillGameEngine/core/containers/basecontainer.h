#pragma once

namespace OK
{
    template<typename T>
    class BaseContainer
    {
    public:
        BaseContainer();
        BaseContainer(const BaseContainer& other);
        BaseContainer(BaseContainer&& other);
        ~BaseContainer();
        BaseContainer& operator=(const BaseContainer& other);
        BaseContainer& operator=(BaseContainer&& other);

        T& operator[](OK::u32 index);
        const T& operator[](OK::u32 index) const;

        void Reserve(OK::u32 reservedSize);
        void Resize(OK::u32 newSize);
        void Clear();

        OK::u32 GetSize() const;
        OK::u32 GetCapacity() const;
        OK::Bool IsEmpty() const;

    protected:
        T* GetRawData();
        const T* GetRawData() const;

        void CopyContent(const T* source, T* destination, OK::u32 itemCount);
        void InitElement(T& element, const T& value);
        void ShutdownElement(T& element);

        OK::u32 m_Size;
        OK::u32 m_MaxSize;

    private:
        T* m_Data;
    };

    template<typename T>
    BaseContainer<T>::BaseContainer()
        : m_Data{ nullptr }
        , m_Size{ 0 }
        , m_MaxSize{ 0 }
    {
    }

    template<typename T>
    BaseContainer<T>::BaseContainer(const BaseContainer& other)
        : m_Data{ new T[other.m_Size] }
        , m_Size{ other.m_Size }
        , m_MaxSize{ other.m_Size }
    {
        CopyContent(other.m_Data, m_Data, other.m_Size);
    }

    template<typename T>
    BaseContainer<T>::BaseContainer(BaseContainer&& other)
        : m_Data{ other.m_Data }
        , m_Size{ other.m_Size }
        , m_MaxSize{ other.m_MaxSize }
    {
        other.m_Data = nullptr;
        other.m_Size = 0;
        other.m_MaxSize = 0;
    }

    template<typename T>
    BaseContainer<T>::~BaseContainer()
    {
        okSafeDeleteArray(m_Data);
    }

    template<typename T>
    BaseContainer<T>& BaseContainer<T>::operator=(const BaseContainer& other)
    {
        m_Data = new T[other.m_Size];
        m_Size = other.m_Size;
        m_MaxSize = other.m_Size;
        CopyContent(other.m_Data, m_Data, other.m_Size);
        return (*this);
    }

    template<typename T>
    BaseContainer<T>& BaseContainer<T>::operator=(BaseContainer&& other)
    {
        m_Data = other.m_Data;
        m_Size = other.m_Size;
        m_MaxSize = other.m_MaxSize;
        other.m_Data = nullptr;
        other.m_Size = 0;
        other.m_MaxSize = 0;
        return (*this);
    }

    template<typename T>
    T& BaseContainer<T>::operator[](OK::u32 index)
    {
        okAssert(index < m_Size, "Invalid index: Provided index is higher than array size.");
        return m_Data[index];
    }

    template<typename T>
    const T& BaseContainer<T>::operator[](OK::u32 index) const
    {
        okAssert(index < m_Size, "Invalid index: Provided index is higher than array size.");
        return m_Data[index];
    }

    template<typename T>
    void BaseContainer<T>::Reserve(OK::u32 reservedSize)
    {
        if (reservedSize > m_MaxSize)
        {
            T* newData = new T[reservedSize];
            if (m_Data != nullptr)
            {
                CopyContent(m_Data, newData, m_Size);
                okSafeDeleteArray(m_Data);
            }
            m_Data = newData;
            m_MaxSize = reservedSize;
        }
    }

    template<typename T>
    void BaseContainer<T>::Resize(OK::u32 newSize)
    {
        Reserve(newSize);
        m_Size = newSize;
    }

    template<typename T>
    void BaseContainer<T>::Clear()
    {
        for (OK::u32 i = 0; i < m_Size; ++i)
        {
            ShutdownElement(m_Data[i]);
        }
        m_Size = 0;
        m_MaxSize = 0;
    }

    template<typename T>
    OK::u32 BaseContainer<T>::GetSize() const
    {
        return m_Size;
    }

    template<typename T>
    OK::u32 BaseContainer<T>::GetCapacity() const
    {
        return m_MaxSize;
    }

    template<typename T>
    OK::Bool BaseContainer<T>::IsEmpty() const
    {
        return m_Size == 0;
    }

    template<typename T>
    T* BaseContainer<T>::GetRawData()
    {
        return m_Data;
    }

    template<typename T>
    const T* BaseContainer<T>::GetRawData() const
    {
        return m_Data;
    }

    template<typename T>
    void BaseContainer<T>::CopyContent(const T* source, T* destination, OK::u32 itemCount)
    {
        // TODO: use OK::MemCopy for trivial types
        for (OK::u32 i = 0; i < m_Size; ++i)
        {
            InitElement(destination[i], source[i]);
        }
    }

#pragma warning( push )
#pragma warning( disable : 4291)

    template<typename T>
    void BaseContainer<T>::InitElement(T& element, const T& value)
    {
        new(&element) T(value);
    }

    template<typename T>
    void BaseContainer<T>::ShutdownElement(T& element)
    {
        element.~T();
    }
#pragma warning( pop ) 
}