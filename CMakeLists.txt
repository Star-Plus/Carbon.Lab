cmake_minimum_required(VERSION 3.10)
project(Carbon)

add_library(Carbon SHARED
    src/components/C14Parser.cpp
)

target_include_directories(Carbon PUBLIC include)