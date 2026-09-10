#pragma once

#include <emper/Types.h>
#include <emper/interfaces/backend/IRenderer.h>

namespace emper::interfaces::module{

enum class ComputeMode : u8
{
    Auto,
    CPU,
    GPU
};

struct ISystemConfig{
    ComputeMode mode = ComputeMode::Auto;
};

class ISystem{
protected:
    ISystemConfig config_;
public:
    virtual ~ISystem() = default;
    void setConfig(const ISystemConfig& config);
    ISystemConfig getConfig() const;

    virtual void initialize() = 0;//  init res,load shaders, etc 
    virtual void tick(f32 dt) = 0;//  update state, run compute, etc
    virtual void shutdown() = 0;//  free res, unload shaders, etc
};

};// namespace emper::interfaces::module
