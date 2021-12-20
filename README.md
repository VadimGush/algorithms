
# Algorithms, data structures and system programming

This repository contains implementation of different algorithms and data structures in C++ and C. Also a couple
of small projects related to system programming.

### Data structures

All data structures are in the `structures` directory. Below is the list of implemented structures.
More documentation and list of methods you can hopefully find in the source code. 

| Class name | Source file  | Description |
| --- | --- | --- |
| `gush::DList<T>` | [DList.h](src/structures/DList.h) | Doubly-linked list |
| `gush::Vector<T>` | [Vector.h](src/structures/Vector.h) | Dynamic array |
| `gush::ArrayStack<T>` | [ArrayStack.h](src/structures/ArrayStack.h) | Stack based on array |
| `gush::ArrayDeque<T>` | [ArrayDeque.h](src/structures/ArrayDeque.h) | Deque based on array |
| `gush::SkiplistSet<T>` | [SkiplistSet.h](src/structures/SkiplistSet.h) | Set implemented with skiplist |
| `gush::BlockStorage<T>` | [BlockStorage.h](src/structures/BlockStorage.h) | Linked list for storing blocks of binary data |

### System programming

Small projects and utils related to UNIX system programming. All placed into `system` directory. 

| File | Description |
| ---  | ----------- |
| [/system/FileDescriptor.h](src/system/FileDescriptor.h) | Wrapper for file descriptors |
| [/system/Environment.h](src/system/Environment.h) | Management of environment variables |
| [/experiments/Operations.h](src/experiments/Operations.h) | Implementation of file system I/O operations |
| [/experiments/Memory.h](src/experiments/Memory.h) | Simple implementations of `malloc()` and `free()` |
| [/experiments/utils/Logging.h](src/experiments/Logging.h) | Implementation for console I/O |
| [/experiments/utils/Auth.h](src/system/Auth.h) | Functions for retrieving user and group information |

### Literature and sources

 * "Open Data Structures (in C++)" by Pat Mortin
 * "The Linux Programming Interface" by Michael Kerrisk

## Literature

 * [Open Data Structures (in C++)](https://opendatastructures.org/ods-cpp.pdf)
 * [The Linux Programming Interface](https://www.amazon.com/Linux-Programming-Interface-System-Handbook-ebook/dp/B004OEJMZM)
