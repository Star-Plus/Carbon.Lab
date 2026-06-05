#pragma once

#include "core/C14Parser.h"
#include "features/apps/docker/DockerComposer.h"

namespace CarbonLab {

    class DockerComposerC14Parser : public C14Parser<DockerComposer> {
    public:
        std::unique_ptr<DockerComposer> parse(const YAML::Node& node) override;
    };

}