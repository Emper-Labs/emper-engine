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

void Simulation::update(f32 dt)
{
    world_.tick(dt);
}

void Simulation::render()
{
    if (!renderer_)
        return;

    renderer_->beginFrame();
    world_.render(*renderer_);
    renderer_->endFrame();
}

bool Simulation::isRunning() const
{
    return running_;
}

void Simulation::requestStop()
{
    running_ = false;
}

void Simulation::tick(f32 dt)
{
    update(dt);
    render();
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