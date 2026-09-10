#include <emper/simulation/system/SystemManager.h>

namespace emper::simulation::system
{
using emper::interfaces::behavior::IRenderable;

void
SystemManager::tick(f32 dt){
    for(auto* system : systems_){
        system->tick(dt);
    }

}

void 
SystemManager::render(IRenderer& renderer)
{
    for (auto* system : systems_)
    {
        if (auto* renderable = dynamic_cast<IRenderable*>(system))
        {
            renderable->render(renderer);
        }
    }
}

void 
SystemManager::add(ISystem& system)
{
    systems_.push_back(&system);
};

void 
SystemManager::remove(ISystem& system)
{

#if (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L) || (__cplusplus >= 202002L)
    std::erase(systems_, &system);
#else
    systems_.erase(
        std::remove(systems_.begin(), systems_.end(), &system),
        systems_.end()
    );
#endif

}

void
SystemManager::initialize()
{
    for (auto* system : systems_)
    {
        system->initialize();
    }
};


void SystemManager::shutdown()
{
    for (auto* system : systems_)
    {
        system->shutdown();
    }
};

}