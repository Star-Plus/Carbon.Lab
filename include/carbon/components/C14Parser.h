#pragma once

#include "core.h"
#include <yaml-cpp/yaml.h>
#include <features/fs/SubFileSystem.h>

namespace CarbonLab {

    class C14Parser {
        
    public:
        C14Parser(const fpath& src);

        void parseFs(SubFileSystem& fs);
    private:
        fpath fileSrc;
        YAML::Node loadedYaml;
    };

}