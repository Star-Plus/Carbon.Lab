#include "FileComparator.h"

#include "fstream"

namespace CarbonLab {

    bool FileComparator::areIdentical() const {
        return sameContent() && sameSize() && sameName();
    }

    bool FileComparator::sameContent() const {
        if (!sameSize()) return false;

        std::ifstream f1(file1, std::ios::binary);
        std::ifstream f2(file2, std::ios::binary);

        return std::equal(
            std::istreambuf_iterator<char>(f1), 
            std::istreambuf_iterator<char>(), 
            std::istreambuf_iterator<char>(f2)
        );
    }

    bool FileComparator::sameSize() const {
        if (!std::filesystem::exists(file1) || !std::filesystem::exists(file2)) return false;

        return std::filesystem::file_size(file1) == std::filesystem::file_size(file2);
    }

    bool FileComparator::sameName() const {
        if (!std::filesystem::exists(file1) || !std::filesystem::exists(file2)) return false;
        
        return std::filesystem::path(file1).filename() == std::filesystem::path(file2).filename();
    }

}