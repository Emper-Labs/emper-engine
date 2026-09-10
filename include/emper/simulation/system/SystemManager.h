#pragma once
#include <emper/interfaces/module/ISystem.h>





/*

Because the operations are currently small;
later on, if there are many operations, 
they should be separated to avoid creating a "God Class."

*/
namespace emper::simulation::system
{
using emper::interfaces::module::ISystem;
using emper::interfaces::backend::IRenderer;

class SystemManager
{
public:
    void add(ISystem& system);
    void remove(ISystem& system);

    void initialize();
    void tick(f32 dt);
    void render(IRenderer& renderer);
    void shutdown();
    
private:
    std::vector<ISystem*> systems_;
};

}