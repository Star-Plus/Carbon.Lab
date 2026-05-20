#include "HttpServiceMockParser.h"
#include "EndpointC14.h"
#include "features/virtualGateway/GatewayServer.h"
#include <memory>

namespace CarbonLab {

    std::unique_ptr<GatewayServer> HttpServiceMockParser::parse(const YAML::Node& node) {

        if (!node["virtual_gateway"].IsDefined()) throw std::runtime_error("Missing 'virutal_gateway' field in config file.");

        auto gateway = node["virtual_gateway"].as<YAML::Node>();
        
        // Iterate over endpoints
        if (gateway["endpoints"].IsDefined()) {
            auto endpoints = gateway["endpoints"].as<YAML::Node>();


            auto gatewayServer = std::make_unique<GatewayServer>();

            for (auto endpoint : endpoints) {
                auto parsedEndpoint = endpoint.second.as<EndpointC14>();

                MockRequest request{parsedEndpoint.request.method, parsedEndpoint.request.url, parsedEndpoint.request.body, parsedEndpoint.request.contentType};
                MockResponse response{parsedEndpoint.response.statusCode, parsedEndpoint.response.contentType, parsedEndpoint.response.body};

                gatewayServer->addMock(MockNetworkData{request, response});
            }

            gatewayServer->launch();

            return gatewayServer;
        }

        throw std::runtime_error("Missing 'endpoints' field in config file.");
    }

}