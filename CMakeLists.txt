cmake_minimum_required(VERSION 3.10)
project(Carbon)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Carbon SHARED

    include/carbon/main.h
    include/carbon/carbon.h
    include/carbon/core.h

    src/components/C14Parser.cpp
    include/carbon/components/C14Parser.h

    include/carbon/features/fs/SubFileSystem.h
    include/carbon/features/fs/File.h
    include/carbon/utils/generators/StringSeeds.h
    src/utils/StringSeeds.cpp
)

include(FetchContent)

FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG yaml-cpp-0.9.0
)
FetchContent_MakeAvailable(yaml-cpp)

target_link_libraries(Carbon PUBLIC yaml-cpp::yaml-cpp)

target_include_directories(Carbon PUBLIC include)
target_include_directories(Carbon PRIVATE include/carbon)


FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.2 # Replace with the latest or specific version tag
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

add_executable(CarbonTests 
  tests/HealthCheck.cpp
)

target_link_libraries(CarbonTests PRIVATE GTest::gtest_main Carbon)

gtest_discover_tests(CarbonTests)