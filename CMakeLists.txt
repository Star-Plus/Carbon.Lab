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

target_include_directories(Carbon PUBLIC include)
target_include_directories(Carbon PRIVATE include/carbon)
