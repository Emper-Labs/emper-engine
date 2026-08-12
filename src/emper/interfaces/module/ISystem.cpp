#include <emper/interfaces/module/ISystem.h>

namespace emper::interfaces::module {

void ISystem::setConfig(const ISystemConfig& config)
{
    config_ = config;
}

ISystemConfig ISystem::getConfig() const
{
    return config_;
}

} // namespace emper::interfaces::module
