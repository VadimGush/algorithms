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

| File | Function | Description |
| --- | --- | --- |
| [FileDescriptor.h](system/types/FileDescriptor.h) |  | Wrapper for file descriptors |
| [Logging.h](system/logging/Logging.h) | | Utils for logging and working with errno variable |
| [Operations.h](system/Operations.h) | `copy(from, to)` | Copies data from one file to another |

### Literature and sources

 * "Open Data Structures (in C++)" by Pat Mortin
 * "The Linux Programming Interface" by Michael Kerrisk

## Building and running

This repository is just a showcase of implementations for different things. It's not written as some kind of
full project that can be used by anyone.

If you want to just play with code from this repository, you can create a new `main.cpp` class and just 
build it using CMake. You can also build this code as a library, but you will need to change CMake build file for that.
And I wouldn't recommend using this code as a library for any projects. Please don't.
