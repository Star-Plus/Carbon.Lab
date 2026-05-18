#include "carbon.h"
#include <gtest/gtest.h>

TEST(EntryTest, InitCarbon) {
    Carbon carbon = Carbon::init("assets/testing/fs-test.yml");
    ASSERT_TRUE(carbon.fs);
}