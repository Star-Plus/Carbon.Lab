#include "SubFileSystem.h"
#include "File.h"
#include "utils/logging/Logger.h"

#include <filesystem>
#include <fstream>
#include <stdexcept>

namespace CarbonLab {

    SubFileSystem::SubFileSystem(const fpath& virtualRoot) : virtualRoot(virtualRoot), logger("SubFileSystem") {
        std::filesystem::create_directories(virtualRoot);
    }

    void SubFileSystem::addFile(const File& file) {

        stagedFiles.push_back(file);
    }

    void SubFileSystem::commit() {
        for (auto& file : stagedFiles) {
            if (file.preRunWrite) {
                writeFile(file);
            }
        }
    }

    void SubFileSystem::writeFile(const File& file) {
        std::filesystem::create_directories(file.virtualPath.parent_path());

        if (file.seedType == SeedType::Copied) {
            if (!file.seedFilePath) {
                throw std::runtime_error("Seed file path" + file.filename + " is not set");
            }

            std::filesystem::copy_file(file.seedFilePath.value(), file.virtualPath);
            return;
        }

        std::ofstream out(file.virtualPath, std::ios::out | std::ios::trunc | std::ios::binary);
        out << file.content;
        out.close();
    }

}