# RUN: cmake --configure .
cmake_minimum_required(VERSION 3.20)

project(Algorithms)
set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wformat=0)

add_executable(algo main.cpp structures/Vector.h structures/ArrayStack.h structures/DList.h structures/ArrayDeque.h structures/SkiplistSet.h system/Operations.cpp system/Operations.h system/utils/FileDescriptor.cpp system/utils/FileDescriptor.h system/utils/Logging.cpp system/utils/Logging.h system/utils/Environment.cpp system/utils/Environment.h system/Memory.h system/utils/Auth.cpp system/utils/Auth.h)
