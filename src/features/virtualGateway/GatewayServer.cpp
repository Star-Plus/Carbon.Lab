#include "GatewayServer.h"
#include "models/MockNetworkData.h"
#include <mutex>

#include "features/environment/Environment.h"

namespace CarbonLab {

    void GatewayServer::addMock(const MockNetworkData& data) {
        std::unique_lock guard(mockTableMutex);

        str rountingKey = data.request.method + "|" + data.request.url;

        if (!mockTable.contains(rountingKey)){
            mockTable[rountingKey] = std::set<MockNetworkData>();
        }

        mockTable[rountingKey].insert(data);
    }


    int GatewayServer::start() {
        int port = server.bind_to_any_port("127.0.0.1");
        setupProxyRouter();

        serverThread = std::thread([this]() {
            server.listen_after_bind();
        });

        server.wait_until_ready();

        this->port = port;

        return port;
    }

    void GatewayServer::stop() {
        if (server.is_running()) {
            server.stop();
        }

        if (serverThread.joinable()) {
            serverThread.join();
        }

        mockTable.clear();
        Environment::remove("HTTP_PROXY");
    }

    void GatewayServer::launch() {
        int port = start();
        Environment::set("HTTP_PROXY", "http://127.0.0.1:" + std::to_string(port));
    }

    void GatewayServer::setupProxyRouter() {
        auto proxyHandler = [this](const httplib::Request& req, httplib::Response& res) {
            std::shared_lock guard(mockTableMutex);

            str routingKey = req.method + "|" + req.path;

            auto it = mockTable.find(routingKey);
            if (it != mockTable.end()) {
                str contentType = req.get_header_value("Content-Type");
                
                auto typicalMockRequest = MockRequest(req.method, req.path, req.body, contentType);
                auto mockNetObj = MockNetworkData(typicalMockRequest, MockResponse());
                
                auto set_it = it->second.find(mockNetObj);
                
                if (set_it != it->second.end()) {
                    const auto& resp = set_it->response;
                    res.status = resp.statusCode;
                    res.set_content(resp.body, resp.contentType);
                    return;
                }
            }

            forwardToRealInternet(req, res);
        };

        server.Get(".*", proxyHandler);
        server.Post(".*", proxyHandler);
        server.Put(".*", proxyHandler);
        server.Delete(".*", proxyHandler);
        server.Patch(".*", proxyHandler);
    }

    void GatewayServer::forwardToRealInternet(const httplib::Request& req, httplib::Response& res) {
        std::string full_url = req.path;

        // This is a shit way to parse the URL, don't forget to use a better parser
        size_t scheme_pos = full_url.find("://");
        if (scheme_pos == std::string::npos) {
            res.status = 400;
            res.set_content("Bad Request: Invalid Proxy URL", "text/plain");
            return;
        }
        
        size_t path_pos = full_url.find('/', scheme_pos + 3);
        std::string host = full_url.substr(0, path_pos);
        std::string path = (path_pos != std::string::npos) ? full_url.substr(path_pos) : "/";

        httplib::Client real_client(host);
        real_client.set_follow_location(true);

        httplib::Result result;
        if (req.method == "GET") {
            result = real_client.Get(path, req.headers);
        } 
        else if (req.method == "POST") {
            std::string content_type = req.get_header_value("Content-Type");
            result = real_client.Post(path, req.headers, req.body, content_type);
        }
        else if (req.method == "PUT") {
            std::string content_type = req.get_header_value("Content-Type");
            result = real_client.Put(path, req.headers, req.body, content_type);
        }
        else if (req.method == "DELETE") {
            result = real_client.Delete(path, req.headers);
        }

        if (result) {
            res.status = result->status;
            res.body = result->body;
            
            for (const auto& header : result->headers) {
                str key = header.first;
                std::transform(key.begin(), key.end(), key.begin(), ::tolower);

                if (key != "content-length" && 
                    key != "transfer-encoding" && 
                    key != "connection" && 
                    key != "keep-alive") {
                    
                    res.set_header(header.first, header.second);
                }
            }
        } else {
            res.status = 502;
            res.set_content("Carbon Gateway Error: Failed to reach real internet.", "text/plain");
        }
    }

}