#pragma once

#include <memory>

#include "core.h"
#include "features/fs/SubFileSystem.h"


class Carbon {

public:
    std::unique_ptr<CarbonLab::SubFileSystem> fs = nullptr;

    static Carbon init(const fpath& c14Path);

    void setFs(CarbonLab::SubFileSystem fs) { this->fs = std::make_unique<CarbonLab::SubFileSystem>(fs); }
};
