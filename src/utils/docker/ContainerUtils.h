#pragma once

#include "core.h"
#include <map>
namespace CarbonLab::Docker {
    std::map<int, int> getMappedHostPorts(const str& containerId);
    void launchDocker();
}