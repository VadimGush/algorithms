
# Algorithms, data structures and system programming

This repository contains implementation of different algorithms and data structures in C++ and C. Also a couple
of small projects related to system programming.

### Data structures

All data structures are in the `structures` directory. Below is the list of implemented structures.
More documentation and list of methods you can hopefully find in the source code. 

Those data structures implemented horribly in terms of safety. Any failed malloc or exception will
result in corrupted state of those classes.

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
| [/system/Auth.h](src/system/Auth.h) | Functions for retrieving user and group information |
| [/experiments/Operations.h](src/experiments/Operations.h) | Implementation of file system I/O operations |
| [/experiments/Memory.h](src/experiments/Memory.h) | Simple implementations of `malloc()` and `free()` |
| [/experiments/Logging.h](src/experiments/Logging.h) | Implementation for console I/O |

## Resources

 * [Book "Open Data Structures (in C++)" by Pat Morin](https://opendatastructures.org/ods-cpp.pdf)
 * [Book "The Linux Programming Interface" by Michael Kerrisk](https://www.amazon.com/Linux-Programming-Interface-System-Handbook-ebook/dp/B004OEJMZM)
