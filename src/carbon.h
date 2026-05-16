#pragma once

#include "core.h"
#include "components/ConfigurationParser.h"
#include "features/fs/SubFileSystem.h"


class Carbon {

public:
    CarbonLab::SubFileSystem fs;

    static void init(const fpath& c14Path);

private:
    CarbonLab::C14Parser c14Parser;

};
