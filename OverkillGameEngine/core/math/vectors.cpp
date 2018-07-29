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
        __m128i vcmp = _mm_castps_si128(_mm_cmpneq_ps(rhs.m_Data, lhs.m_Data));
        OK::u16 test = _mm_movemask_epi8(vcmp);
        return (test == 0);
    }

    OK::Bool operator!=(const Vec4& rhs, const Vec4& lhs)
    {
        return !(rhs == lhs);
    }

    OK::Bool operator> (const Vec4& rhs, const Vec4& lhs)
    {
        __m128i vcmp = _mm_castps_si128(_mm_cmple_ps(rhs.m_Data, lhs.m_Data));
        OK::u16 test = _mm_movemask_epi8(vcmp);
        return (test == 0);
    }

    OK::Bool operator< (const Vec4& rhs, const Vec4& lhs)
    {
        return lhs > rhs;
    }

    OK::Bool operator>=(const Vec4& rhs, const Vec4& lhs)
    {
        return !(lhs < rhs);
    }

    OK::Bool operator<=(const Vec4& rhs, const Vec4& lhs)
    {
        return !(lhs > rhs);
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