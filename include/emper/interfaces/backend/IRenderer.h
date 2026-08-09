#ifndef EMPER_INTERFACES_BACKEND_IRENDERER
#define EMPER_INTERFACES_BACKEND_IRENDERER

#define GPU_BACK_END
#include <emper/ComputeTypes.h>

namespace emper::interfaces::backend {
class IRenderer;
}

namespace emper::interfaces::behavior{

class IRenderable
{
public:
    virtual ~IRenderable() = default;

    virtual void render(
        emper::interfaces::backend::IRenderer& renderer
    ) = 0;
};

};

namespace emper::interfaces::backend {

class IRendererShaderPipeLine //<- cái này chỉ test sau sẽ thêm vào cho engine
{
public:
    virtual ~IRendererShaderPipeLine() = default;

    virtual ProgramHandle createGraphicsProgram(
        const std::string& vertex,
        const std::string& fragment
    ) = 0;

    virtual void destroyProgram(
        ProgramHandle program
    ) = 0;

    virtual void bindProgram(
        ProgramHandle program
    ) = 0;

    virtual void bindStorageBuffer(
        u32 binding,
        BufferHandle buffer
    ) = 0;

    virtual void drawPoints(
        u32 count
    ) = 0;
};

class IRenderer {
public:
    virtual ~IRenderer() = default;
    
    virtual bool processEvents() = 0;

    virtual f32 frameDeltaSeconds() { return 1.0f / 60.0f; }

    virtual void beginFrame() = 0;

    // Colors use the 0xRRGGBBAA layout.
    virtual void drawPoint(f32 x, f32 y, u32 color = 0x3399FFFF) = 0;
    virtual void drawLine(f32 x1, f32 y1,
                          f32 x2, f32 y2, u32 color = 0x3399FFFF) = 0;
    virtual void drawCircle(f32 x, f32 y, f32 radius,
                            u32 color = 0x3399FFFF) = 0;

    virtual void endFrame() = 0;

    // Current drawable surface dimensions. Defaults to 0 so headless/
    // mock renderers compile without overriding them.
    virtual int windowWidth() const { return 0; }
    virtual int windowHeight() const { return 0; }
};
} // namespace emper::interfaces::backend

#endif // EMPER_INTERFACES_BACKEND_IRENDERER
