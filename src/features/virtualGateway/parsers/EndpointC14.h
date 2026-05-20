#pragma once

#include "core.h"
#include "yaml-cpp/node/node.h"
#include <vector>

namespace CarbonLab {

    struct EndpointC14Request {
        str url;
        str method;
        str body;
        str contentType;
        std::vector<std::pair<str, str>> headers;
        std::vector<std::pair<str, str>> queryParams;
    };

    struct EndpointC14Response {
        int statusCode;
        str contentType;
        str body;
        std::vector<std::pair<str, str>> headers;
    };

    struct EndpointC14 {
        EndpointC14Request request;
        EndpointC14Response response;
    };
}

namespace YAML {

    template<>
    struct convert<CarbonLab::EndpointC14Request> {
        static bool decode(const Node& node, CarbonLab::EndpointC14Request& rhs) {
            rhs.url = node["url"].as<str>();
            rhs.method = node["method"].as<str>();
            rhs.body = node["body"].as<str>();
            rhs.contentType = node["content_type"].as<str>();
            rhs.headers = node["headers"].as<std::vector<std::pair<str, str>>>();
            rhs.queryParams = node["query_params"].as<std::vector<std::pair<str, str>>>();
            return true;
        }
    };

    template<>
    struct convert<CarbonLab::EndpointC14Response> {
        static bool decode(const Node& node, CarbonLab::EndpointC14Response& rhs) {
            rhs.statusCode = node["status_code"].as<int>();
            rhs.contentType = node["content_type"].as<str>();
            rhs.body = node["body"].as<str>();
            rhs.headers = node["headers"].as<std::vector<std::pair<str, str>>>();
            return true;
        }
    };

    template<>
    struct convert<CarbonLab::EndpointC14> {
        static bool decode(const Node& node, CarbonLab::EndpointC14& rhs) {
            rhs.request = node["request"].as<CarbonLab::EndpointC14Request>();
            rhs.response = node["response"].as<CarbonLab::EndpointC14Response>();
            return true;
        }
    };
}