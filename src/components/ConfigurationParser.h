#pragma once

#include <yaml-cpp/yaml.h>
#include "core.h"
#include "utils/logging/Logger.h"
#include "yaml-cpp/node/node.h"
#include "core/C14Parser.h"
#include "carbon.h"

namespace CarbonLab {

    enum class ParserType {
        FS
    };

    class ConfigurationParser {
        
    public:
        ConfigurationParser(const fpath& src);
        YAML::Node getYaml() { return loadedYaml; }

        Carbon load();

    private:
        Logger logger;

        fpath fileSrc;
        YAML::Node loadedYaml;
        std::map<ParserType, std::unique_ptr<IC14Parser>> parsers;

    };

}