#pragma once

#include "VirtualFile.h"
#include "core.h"
#include "utilities/FileComparator.h"
#include "utils/logging/Logger.h"
#include <map>
#include <vector>
#include "core/VirtualSystem.h"

namespace CarbonLab {


    class SubFileSystem : public VirtualSystem<SubFileSystem> {
    public:
        SubFileSystem(const fpath& virtualRoot, bool autoCleanup=true);
        SubFileSystem(const fpath& virtualRoot, const std::vector<VirtualFile>& files, bool autoCleanup=true);
        ~SubFileSystem();

        void write(const str& filename, const uint64_t delay=0);
        void trunc(const str& filename, const uint64_t delay=0);

        fpath root() const { return virtualRoot; }
        std::vector<VirtualFile> files() const;

        void addFile(const VirtualFile& file);

        void commit();

        FileComparator comparator(const fpath& file1, const fpath& file2);

        void operator+= (SubFileSystem& other) override;

        friend class FsC14Parser;
    private:
        Logger logger;
        fpath virtualRoot;
        bool autoCleanup = true;
        
        std::map<str, VirtualFile> stagedFiles;

        void writeFile(const VirtualFile& file);
        void truncateFile(const VirtualFile& file);

        void cleanup();
    };

}