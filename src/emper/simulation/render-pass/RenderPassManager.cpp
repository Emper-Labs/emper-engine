#include <emper/simulation/render-pass/RenderPassManager.h>

#include <algorithm>

namespace emper::simulation::render_pass
{

void
RenderPassManager::render(
    RenderPassContext& context)
{
    for (auto* render_pass : render_passes_)
    {
        if (render_pass)
            render_pass->render(context);
    }
}

void
RenderPassManager::add(IRenderPass& renderPass)
{
    render_passes_.push_back(&renderPass);
}

void
RenderPassManager::remove(IRenderPass& renderPass)
{
#if (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L) || (__cplusplus >= 202002L)
    std::erase(render_passes_, &renderPass);
#else
    render_passes_.erase(
        std::remove(
            render_passes_.begin(),
            render_passes_.end(),
            &render_pass
        ),
        render_passes_.end()
    );
#endif
}

}