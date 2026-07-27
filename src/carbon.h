#pragma once

#include <memory>
#include "CarbonExport.h"

#include "features/apps/docker/DockerComposer.h"
#include "features/assertions/AssertionPool.h"
#include "features/fs/SubFileSystem.h"
#include "features/virtualGateway/GatewayServer.h"

namespace CarbonLab {
    class ConfigurationParser;
}

class CARBON_EXPORT Carbon {

public:
    std::unique_ptr<CarbonLab::SubFileSystem> fs = nullptr;
    std::unique_ptr<CarbonLab::GatewayServer> virtualGateway = nullptr;
    std::unique_ptr<CarbonLab::DockerComposer> dockerApps = nullptr;
    
    CarbonLab::AssertionPool assert;

    static Carbon init(const std::filesystem::path& c14Path);
    static Carbon init(const std::filesystem::path& c14Path, const std::string& unit);

    friend class CarbonLab::ConfigurationParser;
};
