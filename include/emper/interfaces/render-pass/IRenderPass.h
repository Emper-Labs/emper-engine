#pragma once

#include <emper/Types.h>
#include <emper/interfaces/backend/IRenderer.h>


namespace emper::interfaces::render_pass
{

using emper::interfaces::backend::IRenderer;

struct RenderPassContext
{
    IRenderer& renderer;

    f32 fps;
    f32 deltaTime;
};

class IRenderPass
{
public:
    virtual ~IRenderPass() = default;

    virtual void render(RenderPassContext& context) = 0;
};

}
