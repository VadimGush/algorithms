cmake_minimum_required(VERSION 3.20)

project(Algorithms)
set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wformat=0)
add_compile_options(-fcoroutines-ts)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

set(sources src/structures/Vector.h src/system/Errno.cpp src/structures/BlockStorage.h src/structures/ArrayStack.h src/structures/DList.h src/structures/ArrayDeque.h src/structures/SkiplistSet.h src/experiments/Operations.cpp src/experiments/Operations.h src/system/FileDescriptor.cpp src/system/FileDescriptor.h src/experiments/Logging.cpp src/experiments/Logging.h src/system/Environment.cpp src/system/Environment.h src/experiments/Memory.h src/system/Auth.cpp src/system/Auth.h)
add_executable(algo main.cpp ${sources})
add_library(gush STATIC ${sources})
