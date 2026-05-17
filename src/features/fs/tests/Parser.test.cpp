#include "components/ConfigurationParser.h"
#include "features/fs/SubFileSystem.h"
#include "features/fs/parsers/FsC14Parser.h"
#include <filesystem>
#include <gtest/gtest.h>

class ParseFsTest : public ::testing::Test {

protected:
    void SetUp() override {
        parser = new CarbonLab::ConfigurationParser("assets/testing/fs-test.yml");
        fsParser = new CarbonLab::FsC14Parser();
    }

    void TearDown() override {
        delete parser;
        delete fsParser;
    }

    CarbonLab::ConfigurationParser* parser;
    CarbonLab::FsC14Parser* fsParser;

};

TEST_F(ParseFsTest, EntryPoint) {
    EXPECT_NO_THROW(fsParser->parse(parser->getYaml()));
}

TEST_F(ParseFsTest, ParseStageFiles) {
    auto fs = fsParser->parse(parser->getYaml());

    EXPECT_EQ(fs.files().size(), 1);

    auto file = fs.files()[0];

    EXPECT_EQ(file.filename, "text.txt");
    EXPECT_EQ(file.seedType, CarbonLab::SeedType::Random);
}

TEST_F(ParseFsTest, CommitFsAfterParsing) {
    auto fs = fsParser->parse(parser->getYaml());
    EXPECT_TRUE(std::filesystem::exists(fs.root() / "text.txt"));
}