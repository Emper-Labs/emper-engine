#pragma once

#include <emper/Types.h>

namespace emper
{

struct SimulationStatistic
{
    f32 fps = 0.0f;
    f32 deltaTime = 0.0f;

    f32 fpsAccumulator = 0.0f;
    u32 fpsFrameCount = 0;
};

}