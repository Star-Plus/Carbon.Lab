#pragma once

#include <memory>

#include "core.h"
#include "features/fs/SubFileSystem.h"
#include "features/virtualGateway/GatewayServer.h"

namespace CarbonLab {
    class ConfigurationParser;
}

class Carbon {

public:
    std::unique_ptr<CarbonLab::SubFileSystem> fs = nullptr;
    std::unique_ptr<CarbonLab::GatewayServer> virtualGateway = nullptr;

    static Carbon init(const fpath& c14Path);

    friend class CarbonLab::ConfigurationParser;

private:

    void setFs(CarbonLab::SubFileSystem fs) { this->fs = std::make_unique<CarbonLab::SubFileSystem>(fs); }
    void setFs(std::unique_ptr<CarbonLab::SubFileSystem> fs) { this->fs = std::move(fs); }

    void setVirtualGateway(std::unique_ptr<CarbonLab::GatewayServer> gateway) { this->virtualGateway = std::move(gateway); }
};
