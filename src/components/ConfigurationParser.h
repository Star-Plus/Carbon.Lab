#pragma once

#include <yaml-cpp/yaml.h>
#include "core.h"
#include "utils/logging/Logger.h"
#include "yaml-cpp/node/node.h"

namespace CarbonLab {

    class ConfigurationParser {
        
    public:
        ConfigurationParser(const fpath& src);
        YAML::Node getYaml() { return loadedYaml; }

    private:
        fpath fileSrc;
        YAML::Node loadedYaml;

        Logger logger;
    };

}