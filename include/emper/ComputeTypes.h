#ifndef EMPER_GPU_TYPES
#define EMPER_GPU_TYPES

#include "Types.h"

#include <string>
#include <vector>

namespace emper{
using BufferHandle = u32;
using ProgramHandle = u32;

struct BufferDesc
{
    std::size_t size = 0;
};

struct DispatchSize
{
    u32 x = 1;
    u32 y = 1;
    u32 z = 1;
};

struct ProgramBinary
{
    std::string hash;
    //GLenum
    u32 format;
    std::vector<std::byte> data;
};

struct ProgramBinaryFile
{
    char magic[4] = {'E','M','P','R'};
    std::uint32_t version = 1;
    std::string hash;
    //GLenum
    u32 format;
    std::vector<std::byte> data;
};
}

#endif