#include <gtest/gtest.h>
#include "utils/os/Shell.h"

TEST(ShellTest, SimpleCoutOfCommand) {
    auto cout = CarbonLab::OS::Shell::exec("echo hello world");
    ASSERT_EQ(cout, "hello world");
}