cmake_minimum_required(VERSION 3.22)
project(launcher)

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_CXX_STANDARD 11)

# src
add_subdirectory(src)
