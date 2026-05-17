#include "FsC14Parser.h"
#include "features/fs/File.h"
#include "features/fs/SubFileSystem.h"
#include "schemas/C14FsSchema.h"
#include "utils/datetime/DateTime.h"
#include "core.h"
#include "utils/generators/UUID.h"

namespace CarbonLab {

    SubFileSystem FsC14Parser::parse(const YAML::Node& node) {
        logger.info("Parsing C14 FS");
        
        auto name = node["name"].as<str>();

        bool autoClean = true;

        if (node["auto_clean"].IsDefined())
            autoClean = node["auto_clean"].as<bool>();

        DateTime now;
        fpath root = fpath("carbon/tests") / name / now.toStr("%Y-%m-%d_%H-%M-%S") / UUID::generateUUID();

        logger.info("Creating test directory: " + root.string());

        SubFileSystem fs(root, autoClean);

        auto fsData = node["fs"].as<C14FsSchema>();

        for (auto file : fsData.files) {
            auto seedType = seedTypeFromStr(file.seedType);

            switch (seedType) {

            case SeedType::Copied:
                fs.addFile(File(file.name, root / file.vpath, file.seed, file.preRunWrite));
                break;

            case SeedType::Random:
                fs.addFile(File(file.name, root / file.vpath, file.seedLength, file.preRunWrite));
                break;

            case SeedType::UC:
                fs.addFile(File(file.name, root / file.vpath, file.seed, file.preRunWrite));
                break;

            default:
                break;
            }
        }

        return fs;
    }

}