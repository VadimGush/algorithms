# RUN: cmake --configure .
cmake_minimum_required(VERSION 3.10)

project(Algorithms)

# will create compile_commands.json to enable code complete 
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(EXECUTABLE_OUTPUT_PATH "bin")

add_compile_options(-Wformat=0)

add_executable(algo tests.c structures/queue.c structures/string.c structures/functions.c structures/set.c structures/vector.c structures/list.c)

