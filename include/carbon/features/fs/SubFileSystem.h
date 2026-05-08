#pragma once

#include "core.h"
#include "File.h"
#include <set>

namespace CarbonLab {

    class C14Parser;

    class SubFileSystem {
    public:
        void write(const str& filename, const uint64_t delay=0);
        void trunc(const str& filename, const uint64_t delay=0);

        fpath root() const { return virtualRoot; }

        friend class C14Parser;
    private:
        fpath virtualRoot;
        std::set<File> stagedFiles;
    };

}