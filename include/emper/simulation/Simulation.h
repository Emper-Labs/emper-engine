#pragma once

#include <emper/interfaces/backend/IRenderer.h>
#include <emper/interfaces/render-pass/IRenderPass.h>

#include <emper/simulation/render-pass/RenderPassManager.h>
#include <emper/simulation/system/SystemManager.h>
#include <emper/simulation/world/World.h>
#include <emper/simulation/SimulationStatistic.h>


namespace emper::simulation
{

using interfaces::backend::IRenderer;
using interfaces::render_pass::IRenderPass;

using interfaces::module::ISystem;

using simulation::render_pass::RenderPassManager;
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

    // Systems
    // Registers a non-owning system.
    void addSystem(ISystem& system);
    void removeSystem(ISystem& system);

    // Render passes
    // Registers a non-owning render pass.
    void addRenderPass(IRenderPass& renderPass);
    void removeRenderPass(IRenderPass& renderPass);

    World& world();
    const World& world() const;

    // Renderer
    // Sets a non-owning renderer.
    void setRenderer(IRenderer& renderer);
    void removeRenderer();

    IRenderer* renderer() const;

private:
    World world_;

    SystemManager systemManager_;
    RenderPassManager renderPassManager_;

    SimulationStatistic statistic_;

    bool running_ = false;

    IRenderer* renderer_ = nullptr;
};

} // namespace emper