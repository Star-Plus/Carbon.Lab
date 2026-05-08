#include "features/fs/SubFileSystem.h"
#include "yaml-cpp/node/parse.h"
#include <components/C14Parser.h>

namespace CarbonLab {
    
    C14Parser::C14Parser(const fpath &src)
    {
        loadedYaml = YAML::LoadFile(src.string());
    }

    void C14Parser::parseFs(SubFileSystem& fs) {
        
    }
}