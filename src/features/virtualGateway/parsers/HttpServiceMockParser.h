#pragma once

#include "core/C14Parser.h"
#include "features/virtualGateway/GatewayServer.h"
#include "yaml-cpp/node/node.h"
#include <memory>
#include "CarbonExport.h"

namespace CarbonLab {

    class CARBON_EXPORT HttpServiceMockParser : public C14Parser<GatewayServer> {
    public:
        std::unique_ptr<GatewayServer> parse(const YAML::Node& node) override;
    };

}