#pragma once

#include "core.h"
namespace CarbonLab {
    
    class FileComparator {
    public:
        FileComparator(const fpath& file1, const fpath& file2) : file1(file1), file2(file2) {}
        
        bool areIdentical() const;
        bool sameContent() const;
        bool sameSize() const;
        bool sameName() const;
        
    private:
        fpath file1, file2;
    };

}