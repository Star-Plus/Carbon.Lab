#include "features/apps/docker/parsers/DockerComposerC14Parser.h"
#include "features/fs/SubFileSystem.h"
#include "features/fs/parsers/FsC14Parser.h"
#include "utils/logging/Logger.h"
#include "yaml-cpp/node/parse.h"
#include "components/ConfigurationParser.h"

#include "features/virtualGateway/parsers/HttpServiceMockParser.h"
#include <memory>

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

        if (loadedYaml["apps"].IsDefined()) {
            if (loadedYaml["apps"]["docker"].IsDefined()) {
                DockerComposerC14Parser parser;
                parsers.insert({ParserType::APPS_DOCKER, std::make_unique<DockerComposerC14Parser>(parser)});
            }
        }
    }

    Carbon ConfigurationParser::load(const str &unit) {
        Carbon carbon;

        auto testName = unit.empty() ? loadedYaml["name"].as<str>() : unit;
        
        if (parsers.contains(ParserType::FS)){
            auto castedParser = static_cast<FsC14Parser*>(parsers[ParserType::FS].get());
            carbon.fs = castedParser->parse(loadedYaml);
        }

        if (parsers.contains(ParserType::V_GS)){
            auto castedParser = static_cast<HttpServiceMockParser*>(parsers[ParserType::V_GS].get());
            carbon.virtualGateway = castedParser->parse(loadedYaml);
        }

        if (parsers.contains(ParserType::APPS_DOCKER)){
            logger.debug("Docker apps parser starting...");
            auto castedParser = static_cast<DockerComposerC14Parser*>(parsers[ParserType::APPS_DOCKER].get());
            carbon.dockerApps = castedParser->parse(loadedYaml);
        }

        if (unit.empty()) {
            if (loadedYaml["suite"].IsDefined()) {
                auto suiteName = loadedYaml["suite"].as<str>();
                carbon.assert = AssertionPool(testName, suiteName);
            }
            else
                carbon.assert = AssertionPool(testName);
        }
        else {
            auto suiteName = loadedYaml["name"].as<str>();
            carbon.assert = AssertionPool(testName, suiteName);

            auto unitFileSrc = loadedYaml["units"][unit]["src"].as<str>();

            ConfigurationParser parser(unitFileSrc);
            auto subCarbon = parser.load(unit);

            if (subCarbon.fs){
                if (carbon.fs)
                    *(carbon.fs) += *(subCarbon.fs);
                else
                    carbon.fs = std::move(subCarbon.fs);
            }

            if (subCarbon.virtualGateway) {
                if (carbon.virtualGateway)
                    *(carbon.virtualGateway) += *(subCarbon.virtualGateway);
                else
                    carbon.virtualGateway = std::move(subCarbon.virtualGateway);
            }
        }

        return carbon;
    }
}