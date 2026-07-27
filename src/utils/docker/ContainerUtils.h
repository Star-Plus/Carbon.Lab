#pragma once

#include "core.h"
#include <map>
#include "CarbonExport.h"

namespace CarbonLab::Docker {
    CARBON_EXPORT std::map<int, int> getMappedHostPorts(const str& containerId);
    CARBON_EXPORT void launchDocker();
}