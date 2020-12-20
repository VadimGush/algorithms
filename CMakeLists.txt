cmake_minimum_required(VERSION 3.10)

project(Algorithms)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(EXECUTABLE_OUTPUT_PATH "bin")

add_executable(algo sandbox.c string.c functions.c set.c vector.c list.c)

