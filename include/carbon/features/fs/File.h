#pragma once

#include "utils/generators/StringSeeds.h"
#include <optional>

namespace CarbonLab {

    class C14Parser;

    enum class SeedType {
        Copied, Random, UC
    };

    class File {
    public:

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

        
        fpath getPath() const { return virtualPath; }
        str getName() const { return filename; }

        friend class C14Parser;

    private:
        std::optional<fpath> seedFilePath = std::nullopt;
        fpath virtualPath;
        str filename;
        str content = "";
        SeedType seedType;
        bool preRunWrite = false;

    };

}