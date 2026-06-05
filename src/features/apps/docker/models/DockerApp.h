#pragma once

#include "core.h"
#include <map>
#include <vector>

namespace CarbonLab {

    struct DockerApp {
        std::map<str, int> ports;
        std::map<str, str> env;
        str name;
        str image;
        str containerId;
    };

    struct DockerAppRequest {
        std::map<str, int> ports;
        std::map<str, str> env;
        std::vector<fpath> initFiles;
        str initCommand;
        str name;
        str image;
        uint64_t minLifetime = 0;
    };

}