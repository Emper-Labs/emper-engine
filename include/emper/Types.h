#ifndef EMPER_TYPES_H
#define EMPER_TYPES_H

#include <cstdint>

namespace emper
{
using i8  = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

using u8  = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using f32 = float;
using f64 = double;



struct Vec2 // need to split math lib 
{
    f32 x = 0.0f;
    f32 y = 0.0f;
};

struct Vec3 // need to split math lib
{
    f32 x = 0.0f;
    f32 y = 0.0f;
    f32 z = 0.0f;
};

inline Vec3 operator+(const Vec3& a, const Vec3& b)
{
    return {
        a.x + b.x,
        a.y + b.y,
        a.z + b.z
    };
}

inline Vec3 operator-(const Vec3& a, const Vec3& b)
{
    return {
        a.x - b.x,
        a.y - b.y,
        a.z - b.z
    };
}

inline Vec3 operator*(const Vec3& v, f32 s)
{
    return {
        v.x * s,
        v.y * s,
        v.z * s
    };
}

inline Vec3 operator*(f32 s, const Vec3& v)
{
    return v * s;
}

inline Vec3 operator/(const Vec3& v, f32 s)
{
    return {
        v.x / s,
        v.y / s,
        v.z / s
    };
}

inline Vec3& operator+=(Vec3& a, const Vec3& b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;

    return a;
}

inline Vec3& operator-=(Vec3& a, const Vec3& b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;

    return a;
}

inline f32 dot(const Vec3& a, const Vec3& b)
{
    return
        a.x * b.x +
        a.y * b.y +
        a.z * b.z;
}

} // namespace emper

#endif // EMPER_TYPES_H