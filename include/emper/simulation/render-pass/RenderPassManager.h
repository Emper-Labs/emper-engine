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
    void add(IRenderPass& render_pass);
    void remove(IRenderPass& render_pass);

    void render(RenderPassContext& context);

private:
    std::vector<IRenderPass*> render_passes_;
};

}