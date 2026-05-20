#pragma once

#include "core.h"
#include "utils/SHA1.h"

namespace CarbonLab {
    struct MockResponse {
        int statusCode;
        str contentType;
        str body;

        MockResponse() {}

        MockResponse(int statusCode, const str& contentType, const str& body) : statusCode(statusCode), contentType(contentType), body(body) {
            SHA1 sha1;
            sha1.update(body);
            sha1.update(contentType);
            hash = sha1.final();
        }

        bool operator < (const MockResponse& other) const { 
            return hash < other.hash;
        }

    private:
        str hash;
    };

    struct MockRequest {
        str method;
        str url;
        str body;
        str contentType;

        MockRequest(const str& method, const str& url, const str& body, const str& contentType) : method(method), url(url), body(body), contentType(contentType) {
            SHA1 sha1;
            sha1.update(method);
            sha1.update(url);
            sha1.update(body);
            sha1.update(contentType);
            hash = sha1.final();
        }

        bool operator < (const MockRequest& other) const { 
            return hash < other.hash;
        }

    private:
        str hash;
    };

    struct MockNetworkData {
        MockRequest request;
        MockResponse response;

        MockNetworkData(const MockRequest& request, const MockResponse& response) : request(request), response(response) {}

        bool operator < (const MockNetworkData& other) const { 
            return request < other.request;
        }
    };
}