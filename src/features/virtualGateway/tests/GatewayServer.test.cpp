#include "features/virtualGateway/GatewayServer.h"
#include <gtest/gtest.h>

TEST(GatewayServer, StartAndStop) {
    CarbonLab::GatewayServer server;
    ASSERT_TRUE(server.start() > 0);
    server.stop();
}

TEST(GatewayServer, AddMock) {
    CarbonLab::GatewayServer server;

    CarbonLab::MockRequest request{"GET", "http://localhost:7111/test", "", ""};
    CarbonLab::MockResponse response{200, "text/plain", "Hello World"};

    server.addMock(CarbonLab::MockNetworkData{request, response});

    auto port = server.start();
    
    httplib::Client client("localhost", 7111);
    client.set_proxy("127.0.0.1", port);

    auto res = client.Get("/test");
    ASSERT_EQ(res->status, 200);
    ASSERT_EQ(res->body, "Hello World");

    server.stop();
}

TEST(GatewayServer, MockMiss) {
    CarbonLab::GatewayServer server;
    auto port = server.start();
    
    httplib::Client client("http://example.com");
    client.set_proxy("127.0.0.1", port);

    auto res = client.Get("/");
    
    ASSERT_TRUE(res) << "The HTTP client failed to get any response! (res is null)";
    
    ASSERT_EQ(res->status, 200);

    server.stop();
}