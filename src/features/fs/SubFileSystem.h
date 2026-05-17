#pragma once

#include "File.h"
#include "core.h"
#include "utils/logging/Logger.h"
#include <map>
#include <vector>

namespace CarbonLab {


    class SubFileSystem {
    public:
        SubFileSystem(const fpath& virtualRoot, bool autoCleanup=true);
        SubFileSystem(const fpath& virtualRoot, const std::vector<File>& files, bool autoCleanup=true);
        ~SubFileSystem();

        void write(const str& filename, const uint64_t delay=0);
        void trunc(const str& filename, const uint64_t delay=0);

        fpath root() const { return virtualRoot; }
        std::vector<File> files() const;

        void addFile(const File& file);

        void commit();

        friend class FsC14Parser;
    private:
        Logger logger;
        fpath virtualRoot;
        bool autoCleanup = true;
        
        std::map<str, File> stagedFiles;

        void writeFile(const File& file);
        void truncateFile(const File& file);

        void cleanup();
    };

}