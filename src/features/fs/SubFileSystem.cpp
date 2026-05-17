#include "SubFileSystem.h"
#include "File.h"
#include "utils/logging/Logger.h"

#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <vector>

namespace CarbonLab {

    SubFileSystem::SubFileSystem(const fpath& virtualRoot, bool autoCleanup) : 
        virtualRoot(virtualRoot), 
        autoCleanup(autoCleanup), 
        logger("SubFileSystem") 
    {
        std::filesystem::create_directories(virtualRoot);
        commit();
    }

    SubFileSystem::SubFileSystem(const fpath& virtualRoot, const std::vector<File>& files, bool autoCleanup) :
        virtualRoot(virtualRoot), 
        autoCleanup(autoCleanup), 
        logger("SubFileSystem")
        {
            std::filesystem::create_directories(virtualRoot);

            for (auto& file : files) {
                stagedFiles.insert({file.filename, file});
            }

            commit();
        }

    SubFileSystem::~SubFileSystem() {
        if (autoCleanup)
            cleanup();
    }

    std::vector<File> SubFileSystem::files() const {
        std::vector<File> files;

        for (auto& [_, file] : stagedFiles) {
            files.push_back(file);
        }

        return files;
    }

    void SubFileSystem::write(const str& filename, const uint64_t delay) {
        auto file = stagedFiles.find(filename);

        if (file == stagedFiles.end()) {
            throw std::runtime_error("File not found: " + filename);
        }

        writeFile(file->second);
    }

    void SubFileSystem::trunc(const str& filename, const uint64_t delay) {
        auto file = stagedFiles.find(filename);

        if (file == stagedFiles.end()) {
            throw std::runtime_error("File not found: " + filename);
        }

        truncateFile(file->second);
    }

    void SubFileSystem::addFile(const File& file) {
        stagedFiles.insert({file.filename, file});
    }

    void SubFileSystem::commit() {
        for (auto& [_, file] : stagedFiles) {
            if (file.preRunWrite) {
                writeFile(file);
            }
        }
    }

    void SubFileSystem::writeFile(const File& file) {
        std::filesystem::create_directories(virtualRoot / file.virtualPath.parent_path());

        if (file.seedType == SeedType::Copied) {
            if (!file.seedFilePath) {
                throw std::runtime_error("Seed file path" + file.filename + " is not set");
            }

            std::filesystem::copy_file(file.seedFilePath.value(), virtualRoot / file.virtualPath);
            return;
        }

        std::ofstream out(virtualRoot / file.virtualPath, std::ios::out | std::ios::trunc | std::ios::binary);
        out << file.content;
        out.close();
    }

    void SubFileSystem::truncateFile(const File& file) {
        std::filesystem::remove(virtualRoot / file.virtualPath);
    }

    void SubFileSystem::cleanup() {
        std::filesystem::remove_all(virtualRoot);
    }
}