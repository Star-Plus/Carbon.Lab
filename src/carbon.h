#pragma once

#include <memory>

#include "features/assertions/AssertionPool.h"
#include "features/fs/SubFileSystem.h"
#include "features/virtualGateway/GatewayServer.h"

namespace CarbonLab {
    class ConfigurationParser;
}

class Carbon {

public:
    std::unique_ptr<CarbonLab::SubFileSystem> fs = nullptr;
    std::unique_ptr<CarbonLab::GatewayServer> virtualGateway = nullptr;
    
    CarbonLab::AssertionPool assert;

    static Carbon init(const std::filesystem::path& c14Path);
    static Carbon init(const std::filesystem::path& c14Path, const std::string& unit);

    friend class CarbonLab::ConfigurationParser;
};
