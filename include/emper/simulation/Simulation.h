#ifndef EMPER_SIMULATION_SIMULATION_H
#define EMPER_SIMULATION_SIMULATION_H

#pragma once

#include <emper/simulation/world/World.h>

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

    void tick();

    World& world();

    const World& world() const;

private:
    World world_;
    bool running_ = false;
};

} // namespace emper

#endif // EMPER_SIMULATION_SIMULATION_H