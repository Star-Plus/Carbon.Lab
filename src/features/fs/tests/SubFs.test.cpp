#include <fstream>
#include <gtest/gtest.h>
#include <sstream>

#include "../SubFileSystem.h"

class SubFsTest : public ::testing::Test {

protected:
    void SetUp() override {
        fs = new CarbonLab::SubFileSystem(fpath("carbon/tests/fsTester"), true);
        fs2 = new CarbonLab::SubFileSystem(fpath("carbon/tests/fsTester2"), false);
    }

    void TearDown() override {
        if (fs != nullptr)
            delete fs;

        if (fs2 != nullptr)
            delete fs2;
    }

    CarbonLab::SubFileSystem* fs, *fs2;
};

TEST_F(SubFsTest, AutoWriteOnRun) {
    fs->addFile(CarbonLab::File("file1", "file1.txt", str("content1"), true));
    fs->addFile(CarbonLab::File("file2", "file2.txt", str("content2"), false));

    fs->commit();

    EXPECT_TRUE(std::filesystem::exists(fs->root() / "file1.txt"));
    EXPECT_FALSE(std::filesystem::exists(fs->root() / "file2.txt"));

    fs->write("file1", 0);
    fs->write("file2", 0);

    EXPECT_TRUE(std::filesystem::exists(fs->root() / "file1.txt"));
    EXPECT_TRUE(std::filesystem::exists(fs->root() / "file2.txt"));
}

TEST_F(SubFsTest, AutoCleanup) {
    auto root1 = fs->root(), root2 = fs2->root();
    delete fs;
    delete fs2;
    fs = nullptr;
    fs2 = nullptr;
    
    EXPECT_FALSE(std::filesystem::exists(root1));
    EXPECT_TRUE(std::filesystem::exists(root2));
}

TEST_F(SubFsTest, CopyFileSeed) {
    fs->addFile(CarbonLab::File("file1", "file1.txt", fpath("assets/testing/seed.txt"), true));

    fs->commit();

    EXPECT_TRUE(std::filesystem::exists(fs->root() / "file1.txt"));

    std::fstream originalSeed("assets/tesging/seed.txt", std::ios::in | std::ios::ate), copiedSeed(fs->root() / "file1.txt", std::ios::in | std::ios::ate);
    
    std::stringstream originalSeedStream, copiedSeedStream;
    originalSeedStream << originalSeed.rdbuf(), copiedSeedStream << copiedSeed.rdbuf();

    EXPECT_EQ(originalSeedStream.str(), copiedSeedStream.str());

    originalSeed.close();
    copiedSeed.close();
}