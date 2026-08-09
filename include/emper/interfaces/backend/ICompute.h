#ifndef EMPER_INTERFACES_BACKEND_ICOMPUTE
#define EMPER_INTERFACES_BACKEND_ICOMPUTE

#include <string>
#include <vector>

#define GPU_BACK_END
#include <emper/ComputeTypes.h>

namespace emper::interfaces::backend {

class IGPUComputeBackend
{
public:
    virtual ~IGPUComputeBackend() = default;

    virtual bool initialize() = 0;

    virtual void shutdown() = 0;

    virtual ProgramHandle createProgram(
        std::string_view source
    ) = 0;

    virtual ProgramHandle compileShader(
        const std::string& path
    ) = 0;

    virtual void destroyProgram(
        ProgramHandle program
    ) = 0;

    virtual BufferHandle createBuffer(
        const BufferDesc& desc
    ) = 0;

    virtual void destroyBuffer(
        BufferHandle buffer
    ) = 0;

    virtual bool writeBuffer(
        BufferHandle buffer,
        const void* data,
        std::size_t size
    ) = 0;

    virtual bool readBuffer(
        BufferHandle buffer,
        void* data,
        std::size_t size
    ) = 0;

    virtual void bindStorageBuffer(
        std::uint32_t binding,
        BufferHandle buffer
    ) = 0;

    virtual void dispatch(
        ProgramHandle program,
        DispatchSize size
    ) = 0;

    virtual void setUniform1f(
        ProgramHandle program,
        const std::string& name,
        float value
    ) = 0;

    virtual void setUniform1i(
        ProgramHandle program,
        const std::string& name,
        int value
    ) = 0;

    virtual void memoryBarrier() = 0;
};



}

#endif//EMPER_INTERFACES_BACKEND_ICOMPUTE