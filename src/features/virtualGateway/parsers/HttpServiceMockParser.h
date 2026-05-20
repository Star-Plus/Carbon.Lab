#pragma once

#include "core/C14Parser.h"
#include "features/virtualGateway/GatewayServer.h"
#include "yaml-cpp/node/node.h"
#include <memory>

namespace CarbonLab {

    class HttpServiceMockParser : public C14Parser<GatewayServer> {
    public:
        std::unique_ptr<GatewayServer> parse(const YAML::Node& node) override;
    };

}