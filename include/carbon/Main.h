#pragma once

#include "components/C14Parser.h"
#include "features/SubFileSystem.h"


class Carbon {

public:
    CarbonLab::SubFileSystem fs;

private:
    CarbonLab::C14Parser c14Parser;

};
