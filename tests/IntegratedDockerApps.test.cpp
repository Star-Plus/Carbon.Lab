#include "carbon.h"
#include <gtest/gtest.h>
TEST(IntegratedDockerAppsTest, DCFile) {
    auto carbon = Carbon::init("assets/testing/dc-test.yml");
    ASSERT_EQ(carbon.dockerApps->connect("test"), "test");
}