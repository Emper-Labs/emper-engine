#include <emper/simulation/world/World.h>

namespace emper::simulation::world
{

std::size_t 
World::objectCount() const
{
    return statistics_.objectCount;
}

const WorldStatistics& 
World::statistics() const
{
    return statistics_;
}
}