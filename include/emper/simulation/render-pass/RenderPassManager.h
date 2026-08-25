#pragma once

#include <emper/interfaces/render-pass/IRenderPass.h>

#include <vector>

namespace emper::simulation::render_pass
{

using emper::interfaces::render_pass::IRenderPass;
using emper::interfaces::render_pass::RenderPassContext;

class RenderPassManager
{
public:
    void add(IRenderPass& renderPass);
    void remove(IRenderPass& renderPass);

    void render(RenderPassContext& context);

private:
    std::vector<IRenderPass*> render_passes_;
};

}