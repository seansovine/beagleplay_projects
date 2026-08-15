cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(BeagleI2C LANGUAGES C)

add_subdirectory(thirdparty)
add_subdirectory(src)
