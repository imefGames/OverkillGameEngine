#include <stdafx.h>
#include <core\math\vectors.h>

#include <emmintrin.h>

namespace OK
{
    Vec4::Vec4()
        : m_Data{}
    {
    }

    Vec4::Vec4(const Vec4& other)
        : m_Data{ other.m_Data }
    {
    }

    Vec4::Vec4(OK::f32 x, OK::f32 y, OK::f32 z, OK::f32 w)
        : m_Data{ _mm_setr_ps(x, y, z, w) }
    {
    }

    OK::f32& Vec4::GetX()
    {
        OK::f32* data = reinterpret_cast<OK::f32*>(&m_Data);
        return data[0];
    }

    OK::f32& Vec4::GetY()
    {
        OK::f32* data = reinterpret_cast<OK::f32*>(&m_Data);
        return data[1];
    }

    OK::f32& Vec4::GetZ()
    {
        OK::f32* data = reinterpret_cast<OK::f32*>(&m_Data);
        return data[2];
    }

    OK::f32& Vec4::GetW()
    {
        OK::f32* data = reinterpret_cast<OK::f32*>(&m_Data);
        return data[3];
    }

    OK::f32 Vec4::GetX() const
    {
        const OK::f32* data = reinterpret_cast<const OK::f32*>(&m_Data);
        return data[0];
    }

    OK::f32 Vec4::GetY() const
    {
        const OK::f32* data = reinterpret_cast<const OK::f32*>(&m_Data);
        return data[1];
    }

    OK::f32 Vec4::GetZ() const
    {
        const OK::f32* data = reinterpret_cast<const OK::f32*>(&m_Data);
        return data[2];
    }

    OK::f32 Vec4::GetW() const
    {
        const OK::f32* data = reinterpret_cast<const OK::f32*>(&m_Data);
        return data[3];
    }

    void Vec4::SetX(OK::f32 x)
    {
        OK::f32* data = reinterpret_cast<OK::f32*>(&m_Data);
        data[0] = x;
    }

    void Vec4::SetY(OK::f32 y)
    {
        OK::f32* data = reinterpret_cast<OK::f32*>(&m_Data);
        data[1] = y;
    }

    void Vec4::SetZ(OK::f32 z)
    {
        OK::f32* data = reinterpret_cast<OK::f32*>(&m_Data);
        data[2] = z;
    }

    void Vec4::SetW(OK::f32 w)
    {
        OK::f32* data = reinterpret_cast<OK::f32*>(&m_Data);
        data[3] = w;
    }

    Vec4& Vec4::operator=(const Vec4& other)
    {
        m_Data = other.m_Data;
        return *this;
    }

    Vec4& Vec4::operator+=(const Vec4& lhs)
    {
        m_Data = _mm_add_ps(m_Data, lhs.m_Data);
        return *this;
    }

    Vec4& Vec4::operator-=(const Vec4& lhs)
    {
        m_Data = _mm_sub_ps(m_Data, lhs.m_Data);
        return *this;
    }

    Vec4& Vec4::operator*=(const Vec4& lhs)
    {
        m_Data = _mm_mul_ps(m_Data, lhs.m_Data);
        return *this;
    }

    Vec4& Vec4::operator/=(const Vec4& lhs)
    {
        m_Data = _mm_div_ps(m_Data, lhs.m_Data);
        return *this;
    }

    Vec4& Vec4::operator+=(OK::f32 scalar)
    {
        __m128 scalarVector = _mm_set1_ps(scalar);
        m_Data = _mm_add_ps(m_Data, scalarVector);
        return *this;
    }

    Vec4& Vec4::operator-=(OK::f32 scalar)
    {
        __m128 scalarVector = _mm_set1_ps(scalar);
        m_Data = _mm_sub_ps(m_Data, scalarVector);
        return *this;
    }

    Vec4& Vec4::operator*=(OK::f32 scalar)
    {
        __m128 scalarVector = _mm_set1_ps(scalar);
        m_Data = _mm_mul_ps(m_Data, scalarVector);
        return *this;
    }

    Vec4& Vec4::operator/=(OK::f32 scalar)
    {
        __m128 scalarVector = _mm_set1_ps(scalar);
        m_Data = _mm_div_ps(m_Data, scalarVector);
        return *this;
    }

    OK::Bool operator==(const Vec4& rhs, const Vec4& lhs)
    {
        return _mm_movemask_ps(_mm_cmpneq_ps(rhs.m_Data, lhs.m_Data)) == 0xff;
    }

    OK::Bool operator!=(const Vec4& rhs, const Vec4& lhs)
    {
        return !(rhs == lhs);
    }

    OK::Bool operator> (const Vec4& rhs, const Vec4& lhs)
    {
        return (_mm_movemask_ps(_mm_cmpgt_ps(rhs.m_Data, lhs.m_Data)) == 0xff);
    }

    OK::Bool operator< (const Vec4& rhs, const Vec4& lhs)
    {
        return lhs > rhs;
    }

    OK::Bool operator>=(const Vec4& rhs, const Vec4& lhs)
    {
        return (_mm_movemask_ps(_mm_cmpge_ps(rhs.m_Data, lhs.m_Data)) == 0xff);
    }

    OK::Bool operator<=(const Vec4& rhs, const Vec4& lhs)
    {
        return (rhs >= lhs);
    }

    Vec4 operator+(const Vec4& rhs, const Vec4& lhs)
    {
        Vec4 retVal{ rhs };
        retVal += lhs;
        return rhs;
    }

    Vec4 operator-(const Vec4& rhs, const Vec4& lhs)
    {
        Vec4 retVal{ rhs };
        retVal -= lhs;
        return rhs;
    }

    Vec4 operator*(const Vec4& rhs, const Vec4& lhs)
    {
        Vec4 retVal{ rhs };
        retVal *= lhs;
        return rhs;
    }

    Vec4 operator/(const Vec4& rhs, const Vec4& lhs)
    {
        Vec4 retVal{ rhs };
        retVal /= lhs;
        return rhs;
    }

    Vec4 operator+(const Vec4& rhs, OK::f32 lhs)
    {
        Vec4 retVal{ rhs };
        retVal += lhs;
        return rhs;
    }

    Vec4 operator-(const Vec4& rhs, OK::f32 lhs)
    {
        Vec4 retVal{ rhs };
        retVal -= lhs;
        return rhs;
    }

    Vec4 operator*(const Vec4& rhs, OK::f32 lhs)
    {
        Vec4 retVal{ rhs };
        retVal *= lhs;
        return rhs;
    }

    Vec4 operator/(const Vec4& rhs, OK::f32 lhs)
    {
        Vec4 retVal{ rhs };
        retVal /= lhs;
        return rhs;
    }
}