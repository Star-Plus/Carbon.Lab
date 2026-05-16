#include <gtest/gtest.h>
#include "utils/generators/UUID.h"

TEST(UUIDTest, UUIDGeneration) {
    auto u1 = CarbonLab::UUID::generateUUID();
    auto u2 = CarbonLab::UUID::generateUUID();

    EXPECT_NE(u1, u2);
}