#include "features/apps/docker/DockerComposer.h"
#include <gtest/gtest.h>
#include "carbon.h"

TEST(DockerComposerTest, SimpleImageLaunch) {
    auto carbon = Carbon::init("assets/testing/unit-test.yml");

    CarbonLab::DockerAppRequest appRequest1 = {
        {{"net", 8080}}, 
        {}, 
        {carbon.fs->root() / carbon.fs->files()[0].virtualPath},
        "echo 'hello world'", 
        "test", 
        "alpine",
        60
    };

    std::vector<CarbonLab::DockerAppRequest> requests = {appRequest1};

    CarbonLab::DockerComposer composer(requests);
    composer.commit();

    ASSERT_FALSE(composer.connect("test", "net").empty());
    ASSERT_NE(composer.connect("test", "net"), "test");
}