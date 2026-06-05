#include "DockerAppC14Definition.h"
#include "DockerComposerC14Parser.h"
#include "features/apps/docker/models/DockerApp.h"

namespace CarbonLab {

    std::unique_ptr<DockerComposer> DockerComposerC14Parser::parse(const YAML::Node& node) {
        if (!node["apps"].IsDefined()) throw std::runtime_error("Missing 'apps' field in config file.");
        if (!node["apps"]["docker"].IsDefined()) throw std::runtime_error("Missing 'docker' field in config file.");

        auto apps = node["apps"]["docker"].as<YAML::Node>();

        if (!apps.IsSequence()) throw std::runtime_error("Invalid 'docker' field in config file.");

        if (apps.size() == 0) throw std::runtime_error("Empty 'docker' field in config file.");

        std::vector<DockerAppRequest> requests = apps.as<std::vector<DockerAppRequest>>();

        if (requests.size() == 0) throw std::runtime_error("Empty 'docker' field in config file.");

        DockerComposer composer(requests);
        return std::make_unique<DockerComposer>(composer);
    }
}