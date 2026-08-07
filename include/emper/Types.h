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

struct Vec2
{
    f32 x = 0.0f;
    f32 y = 0.0f;
};

} // namespace emper

#endif // EMPER_TYPES_H