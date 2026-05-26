#include "features/fs/SubFileSystem.h"
#include <gtest/gtest.h>
#include <vector>

using namespace CarbonLab;

TEST(SubFsComparator, IdenticalFiles) {
    std::vector<VirtualFile> files = {
        VirtualFile("test", fpath("file.txt"), str("content"), true),
        VirtualFile("test2", fpath("folder/file.txt"), str("content"), true),
    };

    SubFileSystem fs(fpath("carbon/tests/fsTester"), files, true);

    EXPECT_TRUE(fs.comparator("file.txt", "folder/file.txt").areIdentical());
}

TEST(SubFsComparator, DifferentFiles) {
    std::vector<VirtualFile> files = {
        VirtualFile("test", fpath("file.txt"), str("content"), true),
        VirtualFile("test2", fpath("folder/file_copy.txt"), str("content"), true),
    };

    SubFileSystem fs(fpath("carbon/tests/fsTester"), files, true);

    EXPECT_FALSE(fs.comparator("file.txt", "folder/file.txt").areIdentical());
}

TEST(SubFsComparator, NonexistentFiles) {
    std::vector<VirtualFile> files = {
        VirtualFile("test", fpath("file.txt"), str("content"), true),
        VirtualFile("test2", fpath("folder/file.txt"), str("content"), true),
    };

    SubFileSystem fs(fpath("carbon/tests/fsTester"), files, true);

    EXPECT_FALSE(fs.comparator("file.txt", "folder/file2.txt").areIdentical());
}

TEST(SubFsComparator, SameContent) {
    std::vector<VirtualFile> files = {
        VirtualFile("test", fpath("file.txt"), str("content"), true),
        VirtualFile("test2", fpath("folder/file.txt"), str("content"), true),
    };

    SubFileSystem fs(fpath("carbon/tests/fsTester"), files, true);

    EXPECT_TRUE(fs.comparator("file.txt", "folder/file.txt").sameContent());
}