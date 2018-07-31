#pragma once

#include <xmmintrin.h> 
#include <core\types.h>

namespace OK
{
    class alignas(16) Vec4
    {
    public:
        Vec4();
        Vec4(const Vec4& other);
        Vec4(OK::f32 x, OK::f32 y = 0.0f, OK::f32 z = 0.0f, OK::f32 w = 0.0f);

        OK::f32 GetX() const;
        OK::f32 GetY() const;
        OK::f32 GetZ() const;
        OK::f32 GetW() const;

        Vec4& operator=(const Vec4& other);

        Vec4& operator+=(const Vec4& lhs);
        Vec4& operator-=(const Vec4& lhs);
        Vec4& operator*=(const Vec4& lhs);
        Vec4& operator/=(const Vec4& lhs);

        Vec4& operator+=(OK::f32 scalar);
        Vec4& operator-=(OK::f32 scalar);
        Vec4& operator*=(OK::f32 scalar);
        Vec4& operator/=(OK::f32 scalar);

        friend OK::Bool operator==(const Vec4& rhs, const Vec4& lhs);
        friend OK::Bool operator> (const Vec4& rhs, const Vec4& lhs);
        friend OK::Bool operator>=(const Vec4& rhs, const Vec4& lhs);

    private:
        __m128 m_Data;
    };

    OK::Bool operator==(const Vec4& rhs, const Vec4& lhs);
    OK::Bool operator!=(const Vec4& rhs, const Vec4& lhs);
    OK::Bool operator> (const Vec4& rhs, const Vec4& lhs);
    OK::Bool operator< (const Vec4& rhs, const Vec4& lhs);
    OK::Bool operator>=(const Vec4& rhs, const Vec4& lhs);
    OK::Bool operator<=(const Vec4& rhs, const Vec4& lhs);

    Vec4 operator+(const Vec4& rhs, const Vec4& lhs);
    Vec4 operator-(const Vec4& rhs, const Vec4& lhs);
    Vec4 operator*(const Vec4& rhs, const Vec4& lhs);
    Vec4 operator/(const Vec4& rhs, const Vec4& lhs);

    Vec4 operator+(const Vec4& rhs, OK::f32 lhs);
    Vec4 operator-(const Vec4& rhs, OK::f32 lhs);
    Vec4 operator*(const Vec4& rhs, OK::f32 lhs);
    Vec4 operator/(const Vec4& rhs, OK::f32 lhs);
}