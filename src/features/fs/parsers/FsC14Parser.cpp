#include "FsC14Parser.h"
#include "features/fs/File.h"
#include "features/fs/SubFileSystem.h"
#include "schemas/C14FsSchema.h"
#include "utils/datetime/DateTime.h"
#include "core.h"
#include "utils/generators/UUID.h"
#include <vector>

namespace CarbonLab {

    SubFileSystem FsC14Parser::parse(const YAML::Node& node) {
        auto name = node["name"].as<str>();
        DateTime now;
        fpath root = fpath("carbon/tests") / name / now.toStr("%Y-%m-%d %H:%M:%S") / UUID::generateUUID();

        SubFileSystem fs(root);

        auto fsData = node["fs"].as<C14FsSchema>();

        std::vector<File> stageFiles;

        for (auto file : fsData.files) {
            auto seedType = seedTypeFromStr(file.seedType);

            switch (seedType) {

            case SeedType::Copied:
                stageFiles.push_back(File(file.name, root / file.vpath, file.seed, file.preRunWrite));
                break;

            case SeedType::Random:
                stageFiles.push_back(File(file.name, root / file.vpath, file.seedLength, file.preRunWrite));
                break;

            case SeedType::UC:
                stageFiles.push_back(File(file.name, root / file.vpath, file.seed, file.preRunWrite));
                break;

            default:
                break;
            }
        }

        fs.stagedFiles = std::move(stageFiles);
        return fs;
    }

}