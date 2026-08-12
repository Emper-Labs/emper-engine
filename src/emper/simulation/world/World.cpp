#include <emper/simulation/world/World.h>

namespace emper::simulation::world
{
void World::setRenderer(interfaces::backend::IRenderer* renderer)
{
    renderer_ = renderer;
}

void World::addSystem(interfaces::module::ISystem* system)
{
    if (system)
    {
        systems_.push_back(system);
    }
};

// Update pass: invoke every registered type's onTick with dt > 0.
// The renderer (if any) is forwarded so callbacks can query surface
// size, but no draw calls should be issued here (they would be
// cleared by the render pass that follows).
void World::tick(f32 dt)
{
    for (auto& [key, storage] : storages_)
    {
        const auto it = onTicks_.find(key);
        if (it != onTicks_.end() && it->second)
        {
            it->second->invoke(storage.get(), dt, renderer_);
        }
    }

    for(auto* system : systems_){
        system->tick(dt);
    }
}

// Render pass: invoke every registered type's onTick with dt == 0
// and the active renderer, so callbacks can issue draw calls between
// beginFrame()/endFrame().
void World::render(interfaces::backend::IRenderer& renderer)
{
    for (auto& [key, storage] : storages_)
    {
        const auto it = onTicks_.find(key);
        if (it != onTicks_.end() && it->second)
        {
            it->second->invoke(storage.get(), 0.0f, &renderer);
        }
    }

    for (auto&system : systems_)
    {
        if (auto* renderable = dynamic_cast<emper::interfaces::behavior::IRenderable*>(system))
        {
            renderable->render(renderer);// <- Render cho những system nào dùng interfaces thôi
        }
    }
}

std::size_t World::objectCount() const
{
    return object_count_;
}

const WorldStatistics& World::statistics() const
{
    return statistics_;
}
}