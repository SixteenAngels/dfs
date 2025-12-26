cmake_minimum_required(VERSION 3.10)
project(dfs_compression C)

set(CMAKE_C_STANDARD 99)

include_directories(include)

file(GLOB SOURCES src/*.c)

add_library(dfs STATIC ${SOURCES})

add_executable(test_dfs test/test_dfs.c)
target_link_libraries(test_dfs dfs)
