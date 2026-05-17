#include "features/fs/SubFileSystem.h"
#include "features/fs/parsers/FsC14Parser.h"
#include "utils/logging/Logger.h"
#include "yaml-cpp/node/parse.h"
#include "components/ConfigurationParser.h"

namespace CarbonLab {
    
    ConfigurationParser::ConfigurationParser(const fpath &src) : logger("C14Parser"), fileSrc(src)
    {
        loadedYaml = YAML::LoadFile(src.string());

        if (loadedYaml["fs"].IsDefined()) {
            FsC14Parser parser;
            parsers.insert({ParserType::FS, parser});
        }
    }

    Carbon ConfigurationParser::load() {
        Carbon carbon;
        
        if (parsers.contains(ParserType::FS)){
            auto castedParser = static_cast<FsC14Parser&>(parsers[ParserType::FS]);
            carbon.setFs(castedParser.parse(loadedYaml["fs"]));
        }

        return carbon;
    }
}