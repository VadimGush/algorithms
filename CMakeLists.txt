cmake_minimum_required(VERSION 3.10)
project(algorithms)

set(CMAKE_CXX_STANDARD 17)

add_executable(algo sandbox.c vector.c set.c functions.c)
set_target_properties(algo PROPERTIES LINKER_LANGUAGE C)
target_compile_options(algo PRIVATE -Wno-format)
