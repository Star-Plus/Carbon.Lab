#pragma once
#include "httplib.h"

#include "models/MockNetworkData.h"
#include <shared_mutex>
#include <thread>
#include <unordered_map>
namespace CarbonLab {

    class GatewayServer {
    public:
        GatewayServer() = default;
        ~GatewayServer() { stop(); }

        void addMock(const MockNetworkData& data);
        int start();
        void stop();

        void launch();

        std::unordered_map<str, std::set<MockNetworkData>>& getMockTable() { return mockTable; }

    private:
        int port;
        httplib::Server server;
        std::thread serverThread;
        std::unordered_map<str, std::set<MockNetworkData>> mockTable;
        mutable std::shared_mutex mockTableMutex;

        void setupProxyRouter();
        void forwardToRealInternet(const httplib::Request& req, httplib::Response& res);
    };

}