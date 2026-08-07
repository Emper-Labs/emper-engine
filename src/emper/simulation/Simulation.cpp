#include <emper/simulation/Simulation.h>

namespace emper
{

void Simulation::initialize()
{
    running_ = false;
}

void Simulation::start()
{
    running_ = true;
}

void Simulation::shutdown()
{
    running_ = false;
}

bool Simulation::isRunning() const
{
    return running_;
}

void Simulation::requestStop()
{
    running_ = false;
}

void Simulation::tick()
{
}

World& Simulation::world()
{
    return world_;
}

const World& Simulation::world() const
{
    return world_;
}

} // namespace emper