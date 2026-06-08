#include <gtest/gtest.h>
#include "features/apps/docker/parsers/DockerComposerC14Parser.h"

TEST(DockerComposerParser, C14Parsing) {
    CarbonLab::DockerComposerC14Parser parser;
    auto result = parser.parse(YAML::LoadFile("assets/testing/dc-test.yml"));
    result->commit();

    ASSERT_GE(result->getLiveApps().size(), 1);
    ASSERT_FALSE(result->connect("test").empty());
    ASSERT_EQ(result->connect("test"), result->getLiveApps()[0]);
}

TEST(DockerComposerParser, DgraphMocking) {
    CarbonLab::DockerComposerC14Parser parser;
    auto result = parser.parse(YAML::LoadFile("assets/testing/MockDGraph.c14"));
    result->commit();

    ASSERT_GE(result->getLiveApps().size(), 1);

    auto connectionString = result->connect("dgraph", "ql");

    // Rebuild
    ASSERT_FALSE(connectionString.empty());
    ASSERT_NE(connectionString, "dgraph");
    ASSERT_NE(connectionString, "dgraph:0");
    std::cout << connectionString << std::endl;
}