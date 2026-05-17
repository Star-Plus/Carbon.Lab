#pragma once

#include <memory>

#include "core.h"
#include "features/fs/SubFileSystem.h"

namespace CarbonLab {
    class ConfigurationParser;
}

class Carbon {

public:
    std::unique_ptr<CarbonLab::SubFileSystem> fs = nullptr;

    static Carbon init(const fpath& c14Path);

    friend class CarbonLab::ConfigurationParser;

private:

    void setFs(CarbonLab::SubFileSystem fs) { this->fs = std::make_unique<CarbonLab::SubFileSystem>(fs); }
};
