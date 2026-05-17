cmake_minimum_required(VERSION 3.10)
project(Carbon)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)


file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS "src/*.h")
file(GLOB_RECURSE TESTING_FILES CONFIGURE_DEPENDS "src/**/*.test.cpp")
file(GLOB_RECURSE GLOBAL_TESTING_FILES CONFIGURE_DEPENDS "test/*.cpp")

list(FILTER SOURCE_FILES EXCLUDE REGEX ".*\\.test\\.cpp$")

add_library(Carbon SHARED
  ${HEADER_FILES}
  ${SOURCE_FILES}
)

target_include_directories(Carbon PUBLIC src)

include(FetchContent)

FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG yaml-cpp-0.9.0
)
FetchContent_MakeAvailable(yaml-cpp)

FetchContent_Declare(
  stduuid
  GIT_REPOSITORY https://github.com/mariusbancila/stduuid.git
  GIT_TAG        v1.2.3
)
FetchContent_MakeAvailable(stduuid)

target_link_libraries(Carbon PUBLIC yaml-cpp::yaml-cpp stduuid)

target_include_directories(Carbon PUBLIC ${stduuid_SOURCE_DIR}/include)


FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.2
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

add_executable(CarbonTests
  ${TESTING_FILES}
  ${GLOBAL_TESTING_FILES}
)

target_compile_options(CarbonTests PRIVATE -Wno-cpp)
target_link_libraries(CarbonTests PRIVATE GTest::gtest_main Carbon)

gtest_discover_tests(CarbonTests)

add_custom_command(TARGET CarbonTests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:CarbonTests>/assets
)