#pragma once

#include <xmmintrin.h>

namespace OK
{
    class alignas(16) Vec4 : public AllocationPolicy<AlignedAllocation<16>>
    {
    public:
        Vec4();
        Vec4(const Vec4& other);
        Vec4(OK::f32 x, OK::f32 y = 0.0f, OK::f32 z = 0.0f, OK::f32 w = 1.0f);

        OK::f32& GetX();
        OK::f32& GetY();
        OK::f32& GetZ();
        OK::f32& GetW();

        OK::f32 GetX() const;
        OK::f32 GetY() const;
        OK::f32 GetZ() const;
        OK::f32 GetW() const;

        void SetX(OK::f32 x);
        void SetY(OK::f32 y);
        void SetZ(OK::f32 z);
        void SetW(OK::f32 w);

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