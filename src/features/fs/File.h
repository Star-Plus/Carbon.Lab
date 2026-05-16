#pragma once

#include "core.h"
#include "utils/generators/StringSeeds.h"
#include <optional>

namespace CarbonLab {

    enum class SeedType {
        Copied, Random, UC
    };

    inline SeedType seedTypeFromStr(const str& str) {
        auto lower = str; std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c) { return std::tolower(c); });

        if (lower == "copied") return SeedType::Copied;
        else if (lower == "random") return SeedType::Random;
        else if (lower == "uc") return SeedType::UC;

        return SeedType::Random;
    }

    struct File {
        File(const str& filename, const fpath& virtualFilePath, const fpath& seedFilePath, bool preRunWrite=false) : 
            filename(filename) ,seedFilePath(seedFilePath), virtualPath(virtualFilePath), preRunWrite(preRunWrite), seedType(SeedType::Copied) {}
            
        File(const str& filename, const fpath& virtualFilePath, const str& content, bool preRunWrite=false) :
            filename(filename), virtualPath(virtualFilePath), preRunWrite(preRunWrite), content(content), seedType(SeedType::UC) {}

        File(const str& filename, const fpath& virtualFilePath, const size_t randomContentLength=30, bool preRunWrite=false) :
            filename(filename), virtualPath(virtualFilePath), preRunWrite(preRunWrite) , seedType(SeedType::Random)
            {
                // Generate random content
                content = Seeds::generateRandomString(randomContentLength);
            }
            
        std::optional<fpath> seedFilePath = std::nullopt;
        fpath virtualPath;
        str filename;
        str content = "";
        SeedType seedType;
        bool preRunWrite = false;

    };

}