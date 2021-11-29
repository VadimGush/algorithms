![](https://github.com/vadimgush/algorithms/workflows/CMake/badge.svg)

# Algorithms, data structures and system programming

This repository contains implementation of different algorithms and data structures in C++ and C. Also a couple
of small projects related to system programming.

### Data structures

All data structures are in the `structures` directory. Below is the list of implemented structures.
More documentation and list of methods you can hopefully find in the source code. 

| Class name | Source file  | Description |
| --- | --- | --- |
| `gush::DList<T>` | [DList.h](structures/DList.h) | Doubly-linked list |
| `gush::Vector<T>` | [Vector.h](structures/Vector.h) | Dynamic array |
| `gush::ArrayStack<T>` | [ArrayStack.h](structures/ArrayStack.h) | Stack based on array |
| `gush::ArrayDeque<T>` | [ArrayDeque.h](structures/ArrayDeque.h) | Deque based on array |
| `gush::SkiplistSet<T>` | [SkiplistSet.h](structures/SkiplistSet.h) | Set implemented with skiplist |


### System programming

Small projects and utils related to UNIX system programming. All placed into `system` directory. 

| File | Description |
| ---  | ----------- |
| [/system/Operations.h](system/Operations.h) | Implementation of I/O operations |
| [/system/Memory.h](system/Memory.h) | Simple implementations of `malloc()` and `free()` |
| [/system/utils/FileDescriptor.h](system/utils/FileDescriptor.h) | Wrapper for file descriptors |
| [/system/utils/Environment.h](system/utils/Environment.h) | Management of environment variables |
| [/system/utils/Logging.h](system/utils/Logging.h) | Implementation for terminal I/O |
| [/system/utils/Auth.h](system/Auth.h) | Functions for retrieving user and group information |

## Building and running

This repository is just a showcase of implementations for different things. It's not written as some kind of
full project that can be used by anyone.

If you want to just play with code from this repository, you can create a new `main.cpp` file and just 
build it using CMake. You can also build this code as a library, but you will need to change CMake build file for that.
And I wouldn't recommend using this code as a library for any projects. Please don't.

## Literature

 * [Open Data Structures (in C++)](https://opendatastructures.org/ods-cpp.pdf)
 * [The Linux Programming Interface](https://www.amazon.com/Linux-Programming-Interface-System-Handbook-ebook/dp/B004OEJMZM)
