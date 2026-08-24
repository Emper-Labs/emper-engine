#pragma once

#include <emper/interfaces/backend/IRenderer.h>
#include <emper/simulation/system/SystemManager.h>
#include <emper/simulation/world/World.h>

namespace emper
{

using interfaces::backend::IRenderer;
using interfaces::module::ISystem;
using simulation::system::SystemManager;
using simulation::world::World;

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

    // Registers a non-owning system.
    void addSystem(ISystem& system);
    void removeSystem(ISystem& system);

    World& world();
    const World& world() const;

    // Sets a non-owning renderer.
    void setRenderer(IRenderer& renderer);
    void removeRenderer();

    IRenderer* renderer() const;

private:
    World world_;
    SystemManager systemManager_;

    bool running_ = false;
    IRenderer* renderer_ = nullptr;
};

} // namespace emper