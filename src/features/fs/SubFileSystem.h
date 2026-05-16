#pragma once

#include "File.h"
#include <vector>

namespace CarbonLab {


    class SubFileSystem {
    public:
        SubFileSystem(const fpath& virtualRoot) : virtualRoot(virtualRoot) {}

        void write(const str& filename, const uint64_t delay=0);
        void trunc(const str& filename, const uint64_t delay=0);

        fpath root() const { return virtualRoot; }
        std::vector<File> files() const { return stagedFiles; }

        friend class FsC14Parser;
    private:
        fpath virtualRoot;
        std::vector<File> stagedFiles;
    };

}