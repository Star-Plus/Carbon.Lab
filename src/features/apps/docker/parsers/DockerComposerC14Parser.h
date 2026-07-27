#pragma once

#include "core/C14Parser.h"
#include "features/apps/docker/DockerComposer.h"

#include "CarbonExport.h"

namespace CarbonLab {

    class CARBON_EXPORT DockerComposerC14Parser : public C14Parser<DockerComposer> {
    public:
        std::unique_ptr<DockerComposer> parse(const YAML::Node& node) override;
    };

}