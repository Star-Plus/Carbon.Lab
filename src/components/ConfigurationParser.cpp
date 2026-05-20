#include "features/fs/SubFileSystem.h"
#include "features/fs/parsers/FsC14Parser.h"
#include "utils/logging/Logger.h"
#include "yaml-cpp/node/parse.h"
#include "components/ConfigurationParser.h"

#include "features/virtualGateway/parsers/HttpServiceMockParser.h"

namespace CarbonLab {
    
    ConfigurationParser::ConfigurationParser(const fpath &src) : logger("C14Parser"), fileSrc(src)
    {
        loadedYaml = YAML::LoadFile(src.string());

        if (loadedYaml["fs"].IsDefined() || loadedYaml["filesystem"].IsDefined()) {
            FsC14Parser parser;
            parsers.insert({ParserType::FS, std::make_unique<FsC14Parser>(parser)});
        }

        if (loadedYaml["virtual_gateway"].IsDefined()) {
            HttpServiceMockParser parser;
            parsers.insert({ParserType::V_GS, std::make_unique<HttpServiceMockParser>(parser)});
        }
    }

    Carbon ConfigurationParser::load() {
        Carbon carbon;
        
        if (parsers.contains(ParserType::FS)){
            auto castedParser = static_cast<FsC14Parser*>(parsers[ParserType::FS].get());
            carbon.setFs(castedParser->parse(loadedYaml));
        }

        if (parsers.contains(ParserType::V_GS)){
            auto castedParser = static_cast<HttpServiceMockParser*>(parsers[ParserType::V_GS].get());
            carbon.setVirtualGateway(castedParser->parse(loadedYaml));
        }

        return carbon;
    }
}