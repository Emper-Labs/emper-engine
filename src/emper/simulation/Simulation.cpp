#include <emper/simulation/Simulation.h>

#include <algorithm>

namespace emper::simulation
{
using emper::interfaces::render_pass::RenderPassContext;

void 
Simulation::initialize()
{
    running_ = false;
}

void 
Simulation::start()
{
    running_ = true;
}

void 
Simulation::shutdown()
{
    running_ = false;
}

void 
Simulation::update(f32 dt)
{
    systemManager_.tick(dt);
}

void 
Simulation::render()
{
    if (!renderer_)
        return;

    renderer_->beginFrame();

    systemManager_.render(*renderer_);
    
    RenderPassContext context{
        .renderer = *renderer_,
        .fps = statistic_.fps,
        .deltaTime = statistic_.deltaTime
    };

    renderPassManager_.render(context);

    renderer_->endFrame();
}

void 
Simulation::addSystem(ISystem& system)
{
    systemManager_.add(system);
}

void 
Simulation::removeSystem(ISystem& system)
{
    systemManager_.remove(system);
}

void 
Simulation::addRenderPass(IRenderPass& renderPass){
    renderPassManager_.add(renderPass);
}

void 
Simulation::removeRenderPass(IRenderPass& renderPass){
    renderPassManager_.remove(renderPass);
}


bool 
Simulation::isRunning() const
{
    return running_;
}

void 
Simulation::requestStop()
{
    running_ = false;
}

void 
Simulation::tick(f32 dt)
{
    statistic_.deltaTime = dt;

    statistic_.fpsAccumulator += dt;
    ++statistic_.fpsFrameCount;

    if (statistic_.fpsAccumulator >= 1.0f)
    {
        statistic_.fps =
            static_cast<f32>(statistic_.fpsFrameCount) /
            statistic_.fpsAccumulator;

        statistic_.fpsAccumulator = 0.0f;
        statistic_.fpsFrameCount = 0;
    }

    update(dt);
    render();
}

bool 
Simulation::tick()
{
    if (!running_)
        return false;

    if (renderer_ && !renderer_->processEvents())
    {
        requestStop();
        return false;
    }

    const f32 dt = renderer_
        ? std::clamp(
            renderer_->frameDeltaSeconds(),
            0.0f,
            0.05f
        )
        : 1.0f / 60.0f;

    tick(dt);

    return running_;
}

World& 
Simulation::world()
{
    return world_;
}

const 
World& Simulation::world() const
{
    return world_;
}

void 
Simulation::setRenderer(IRenderer& renderer)
{
    renderer_ = &renderer;
}

void 
Simulation::removeRenderer()
{
    renderer_ = nullptr;
}

IRenderer* 
Simulation::renderer() const
{
    return renderer_;
}

} // namespace emper