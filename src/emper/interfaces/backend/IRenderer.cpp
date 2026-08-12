#include <emper/interfaces/backend/IRenderer.h>

namespace emper::interfaces::backend {

f32 IRenderer::frameDeltaSeconds()
{
    return 1.0f / 60.0f;
}

int IRenderer::windowWidth() const
{
    // Defaults to 0 so headless / mock renderers compile without
    // overriding these methods.
    return 0;
}

int IRenderer::windowHeight() const
{
    return 0;
}

} // namespace emper::interfaces::backend
