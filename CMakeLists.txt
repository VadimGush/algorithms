# RUN: cmake --configure .
cmake_minimum_required(VERSION 3.20)

project(Algorithms)
set(CMAKE_CXX_STANDARD 20)

set(EXECUTABLE_OUTPUT_PATH "bin")
add_compile_options(-Wformat=0)

add_executable(algo src/main.cpp src/structure/vector.h)
