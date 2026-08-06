cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(BeagleI2C LANGUAGES C)

add_executable(hello src/hello.c)
add_executable(i2c src/hello_i2c.c)

