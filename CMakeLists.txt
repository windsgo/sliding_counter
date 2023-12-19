cmake_minimum_required(VERSION 3.15)
project(sliding_counter LANGUAGES C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RELEASE)
endif()

add_subdirectory(src)
add_subdirectory(test)