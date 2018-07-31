#include <core\asserts.h>
#include <core\types.h>

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

    private:
        OK::u32 m_Size;
        OK::u32 m_MaxSize;
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
        for (OK::u32 i = 0; i < other.m_Size; ++i)
        {
            m_Data[i] = other.m_Data[i];
        }
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
        delete[] m_Data;
    }

    template<typename T>
    BaseContainer& BaseContainer<T>::operator=(const BaseContainer& other)
    {
        m_Data = new T[other.m_Size];
        m_Size = other.m_Size;
        m_MaxSize = other.m_Size;
        for (OK::u32 i = 0; i < other.m_Size; ++i)
        {
            m_Data[i] = other.m_Data[i];
        }
        return (*this);
    }

    template<typename T>
    BaseContainer& BaseContainer<T>::operator=(BaseContainer&& other)
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
            newData = new T[reservedSize];
            for (OK::u32 i = 0; i < m_Size; ++i)
            {
                newData[i] = m_Data[i];
            }
            delete[] m_Data;
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
}