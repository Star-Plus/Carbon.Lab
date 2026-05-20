#include <gtest/gtest.h>
#include <memory>
#include "components/ConfigurationParser.h"
#include "features/virtualGateway/GatewayServer.h"
#include "features/virtualGateway/parsers/HttpServiceMockParser.h"

TEST(GatewayParserTest, EntryPoint) {
    auto parser = CarbonLab::ConfigurationParser("assets/testing/gate-test.yml");
    auto gatewayParser = CarbonLab::HttpServiceMockParser();

    std::unique_ptr<CarbonLab::GatewayServer> gateway = nullptr;

    EXPECT_NO_THROW(gateway = gatewayParser.parse(parser.getYaml()));

    EXPECT_EQ(gateway->getMockTable().size(), 1);
}

TEST(GatewayParserTest, Launch) {
    auto parser = CarbonLab::ConfigurationParser("assets/testing/gate-test.yml");
    auto gatewayParser = CarbonLab::HttpServiceMockParser();

    std::unique_ptr<CarbonLab::GatewayServer> gateway = nullptr;

    EXPECT_NO_THROW(gateway = gatewayParser.parse(parser.getYaml()));

    EXPECT_EQ(gateway->getMockTable().size(), 1);

    EXPECT_NO_THROW(gateway->stop());
}