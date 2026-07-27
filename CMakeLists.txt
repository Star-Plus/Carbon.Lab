cmake_minimum_required(VERSION 3.10)
project(Carbon)

if(WIN32)
    add_compile_definitions(_WIN32_WINNT=0x0A00)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)


file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS "src/*.h")
file(GLOB_RECURSE TESTING_FILES CONFIGURE_DEPENDS "src/**/*.test.cpp")
file(GLOB_RECURSE GLOBAL_TESTING_FILES CONFIGURE_DEPENDS "tests/*.cpp")

list(FILTER SOURCE_FILES EXCLUDE REGEX ".*\\.test\\.cpp$")

add_library(Carbon SHARED
  ${HEADER_FILES}
  ${SOURCE_FILES}
)

include(GenerateExportHeader)
generate_export_header(Carbon
  EXPORT_MACRO_NAME CARBON_EXPORT
  EXPORT_FILE_NAME CarbonExport.h
)

target_include_directories(Carbon PUBLIC src $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)

include(FetchContent)

set(YAML_CPP_BUILD_CONTRIB OFF CACHE BOOL "" FORCE)
set(YAML_CPP_BUILD_TOOLS OFF CACHE BOOL "" FORCE)
set(YAML_CPP_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# YAML

FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG yaml-cpp-0.9.0
)
FetchContent_MakeAvailable(yaml-cpp)

# UUID

FetchContent_Declare(
  stduuid
  GIT_REPOSITORY https://github.com/mariusbancila/stduuid.git
  GIT_TAG        v1.2.3
)
FetchContent_MakeAvailable(stduuid)

# Http Library

set(HTTPLIB_USE_ZSTD_IF_AVAILABLE OFF CACHE BOOL "" FORCE)
set(HTTPLIB_USE_NON_BLOCKING_GETADDRINFO OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
  httplib
  GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
  GIT_TAG        v0.45.0
)
FetchContent_MakeAvailable(httplib)

target_link_libraries(Carbon PUBLIC yaml-cpp::yaml-cpp stduuid httplib::httplib)

target_include_directories(Carbon PUBLIC ${stduuid_SOURCE_DIR}/include)

# GTest

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

target_compile_options(CarbonTests PRIVATE $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wno-cpp>)
target_link_libraries(CarbonTests PRIVATE Carbon gtest gtest_main)

gtest_discover_tests(CarbonTests)

add_custom_command(TARGET CarbonTests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:CarbonTests>/assets
)