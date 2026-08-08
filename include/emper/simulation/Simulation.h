#ifndef EMPER_SIMULATION_SIMULATION_H
#define EMPER_SIMULATION_SIMULATION_H

#pragma once

#include <emper/simulation/world/World.h>
#include <emper/interfaces/backend/IRenderer.h>

namespace emper
{

class Simulation
{
public:
    Simulation() = default;

    ~Simulation() = default;

    void initialize();

    void start();

    void shutdown();

    bool isRunning() const;

    void requestStop();

    void tick(f32 dt);

    bool tick();

    void update(f32 dt);

    void render();

    emper::simulation::world::World& world();

    const emper::simulation::world::World& world() const;

    void setRenderer(emper::interfaces::backend::IRenderer* renderer)
    {
        renderer_ = renderer;
        world_.setRenderer(renderer);
    }

    emper::interfaces::backend::IRenderer* renderer() const
    {
        return renderer_;
    }

private:
    emper::simulation::world::World world_;
    bool running_ = false;
    emper::interfaces::backend::IRenderer* renderer_ = nullptr;
};

} // namespace emper

#endif // EMPER_SIMULATION_SIMULATION_H