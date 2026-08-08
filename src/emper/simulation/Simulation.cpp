#include <emper/simulation/Simulation.h>

#include <algorithm>

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

bool Simulation::tick()
{
    if (!running_)
    {
        return false;
    }

    if (renderer_ && !renderer_->processEvents())
    {
        requestStop();
        return false;
    }

    const f32 dt = renderer_
        ? std::clamp(renderer_->frameDeltaSeconds(), 0.0f, 0.05f)
        : 1.0f / 60.0f;

    tick(dt);
    return running_;
}

emper::simulation::world::World& Simulation::world()
{
    return world_;
}

const emper::simulation::world::World& Simulation::world() const
{
    return world_;
}

} // namespace emper