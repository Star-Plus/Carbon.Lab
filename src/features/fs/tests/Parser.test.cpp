#include "components/ConfigurationParser.h"
#include "features/fs/SubFileSystem.h"
#include "features/fs/parsers/FsC14Parser.h"
#include <gtest/gtest.h>

class ParseFsTest : public ::testing::Test {

protected:
    void SetUp() override {
        parser = new CarbonLab::ConfigurationParser("assets/fs-test.yml");
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
    CarbonLab::ConfigurationParser parser("assets/fs-test.yml");
    CarbonLab::FsC14Parser fsParser;

    auto fs = fsParser.parse(parser.getYaml());

    EXPECT_EQ(fs.files().size(), 1);

    auto file = fs.files()[0];

    EXPECT_EQ(file.filename, "text.txt");
    EXPECT_EQ(file.seedType, CarbonLab::SeedType::Random);
}