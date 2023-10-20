
# Algorithms and data structures

This repository contains implementation of different algorithms and data structures in C++.

### Data structures

Below is the list of implemented structures. Don't use them anywhere. They're not safe and not properly tested.

| Class name | Source file  | Description |
| --- | --- | --- |
| `dlist<T>` | [dlist.h](source/dlist.h) | Doubly-linked list |
| `vector<T>` | [vector.h](source/vector.h) | Dynamic array |
| `array_stack<T>` | [array_stack.h](source/array_stack.h) | Stack based on array |
| `array_deque<T>` | [array_deque.h](source/array_deque.h) | Deque based on array |
| `skiplist_set<T>` | [skiplist_set.h](source/skiplist_set.h) | Set implemented with skiplist |
| `block_storage<T>` | [block_storage.h](source/block_storage.h) | Linked list for storing blocks of binary data |

### How to test

To run tests using GTest suite:
```sh
mkdir build
cd build

cmake ../
cmake --build .
ctest
```

## Resources

 * [Book "Open Data Structures (in C++)" by Pat Morin](https://opendatastructures.org/ods-cpp.pdf)
