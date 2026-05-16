#include "core/C14Parser.h"
#include "features/fs/SubFileSystem.h"

namespace CarbonLab {

    class FsC14Parser : public C14Parser<SubFileSystem> {
    public:
        SubFileSystem parse(const YAML::Node& node) override;
    };

}