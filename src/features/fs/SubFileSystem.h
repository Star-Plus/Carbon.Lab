#pragma once

#include "File.h"
#include "utils/logging/Logger.h"
#include <vector>

namespace CarbonLab {


    class SubFileSystem {
    public:
        SubFileSystem(const fpath& virtualRoot);
        SubFileSystem(SubFileSystem&&) = default;
        SubFileSystem& operator=(SubFileSystem&&) = default;

        void write(const str& filename, const uint64_t delay=0);
        void trunc(const str& filename, const uint64_t delay=0);

        fpath root() const { return virtualRoot; }
        std::vector<File> files() const { return stagedFiles; }

        void clear() { stagedFiles.clear(); }

        void addFile(const File& file);

        void commit();

        friend class FsC14Parser;
    private:
        Logger logger;
        fpath virtualRoot;
        std::vector<File> stagedFiles;

        void writeFile(const File& file);
        void truncateFile(const File& file);
    };

}