#include "utils/logging/Logger.h"
#include "yaml-cpp/node/parse.h"
#include "components/ConfigurationParser.h"

namespace CarbonLab {
    
    ConfigurationParser::ConfigurationParser(const fpath &src) : logger("C14Parser"), fileSrc(src)
    {
        loadedYaml = YAML::LoadFile(src.string());
    }
}