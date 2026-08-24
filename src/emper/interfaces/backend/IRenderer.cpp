#include <emper/interfaces/backend/IRenderer.h>
namespace emper::interfaces::backend {

f32 
IRenderer::frameDeltaSeconds()
{
    return 1.0f / 60.0f;
}

i32 
IRenderer::windowWidth() const
{
    return 0;
}

i32 
IRenderer::windowHeight() const
{
    return 0;
}

} // namespace emper::interfaces::backend
