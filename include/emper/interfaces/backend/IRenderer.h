#ifndef EMPER_INTERFACES_BACKEND_RENDERER
#define EMPER_INTERFACES_BACKEND_RENDERER

namespace emper::interfaces::backend{
class IRenderer {
public:
    virtual ~IRenderer() = default;
    
    virtual bool processEvents() = 0;

    virtual void beginFrame() = 0;

    virtual void drawPoint(float x, float y) = 0;
    virtual void drawLine(float x1, float y1,
                          float x2, float y2) = 0;
    virtual void drawCircle(float x, float y, float radius) = 0;

    virtual void endFrame() = 0;

    // Current drawable surface dimensions. Defaults to 0 so headless/
    // mock renderers compile without overriding them.
    virtual int windowWidth() const { return 0; }
    virtual int windowHeight() const { return 0; }
};
}

#endif//EMPER_INTERFACES_BACKEND_RENDERER
