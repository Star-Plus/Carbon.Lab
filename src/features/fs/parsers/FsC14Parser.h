#pragma once

#include "core/C14Parser.h"
#include "features/fs/SubFileSystem.h"
#include "utils/logging/Logger.h"

namespace CarbonLab {

    class FsC14Parser : public C14Parser<SubFileSystem> {
    public:
        FsC14Parser() : logger("FsC14Parser") {}
        SubFileSystem parse(const YAML::Node& node) override;

    private:
        Logger logger;
    };

}