#include <gtest/gtest.h>
#include "utils/docker/ContainerUtils.h"

TEST(ContainerUtilsTest, GetMappedPort) {

    int result = system("docker info > /dev/null 2>&1");

    if (result != 0) {
        #ifdef _WIN32
            system("docker desktop start");
        #elif defined(__linux__)
            system("sudo systemctl start docker");
        #endif
    }

    system("docker rm -f test > /dev/null 2>&1");
    system("docker run -d --name test -p 6020:8080 alpine sleep 60");
    auto ports = CarbonLab::Docker::getMappedHostPorts("test");
    EXPECT_EQ(ports.size(), 1);
    EXPECT_EQ(ports[8080], 6020);
    system("docker rm -f test");
}