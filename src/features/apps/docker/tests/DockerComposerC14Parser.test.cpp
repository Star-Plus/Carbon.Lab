#include <gtest/gtest.h>
#include "features/apps/docker/parsers/DockerComposerC14Parser.h"

TEST(DockerComposerParser, C14Parsing) {
    CarbonLab::DockerComposerC14Parser parser;
    auto result = parser.parse(YAML::LoadFile("assets/testing/dc-test.yml"));
    result->commit();

    // Rebuild
    ASSERT_GE(result->getLiveApps().size(), 1);
    ASSERT_FALSE(result->connect("test").empty());
    ASSERT_EQ(result->connect("test"), result->getLiveApps()[0]);
}