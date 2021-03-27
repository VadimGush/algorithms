![](https://github.com/vadimgush/algorithms/workflows/CMake/badge.svg)

# Algorithms and data structures

Implementation of different algorithms and data structures in C.

### Algorithms

| Algorithm                             | Source file / function name                         | Time complexity       | Space complexity  |
| ------------------------------------- | --------------------------------------------------- | --------------------- | ----------------- |
| Linear search                         | `vector.c / vector_find()`                          | ``O(N)``              |                   |
| Invert array                          | `vector.c / vector_invert()`                        | ``O(N)``              |                   |
| Cyclic shift of array to right/left   | `vector.c / vector_shift_...()`                     | ``O(N)``              |                   |
| Search in text                        | `string.c / string_find()`                          | ``O(N*I)``            |                   |
| Insert sort                           | `vector.c / vector_insert_sort()`                   | ``O(N^2)``            | ``O(1)``          |
| Choice sort                           | `vector.c / vector_choice_sort()`                   | ``O(N^2)``            | ``O(1)``          |
| Bubble sort                           | `vector.c / vector_bubble_sort()`                   | ``O(N^2)``            | ``O(1)``          |
| Count sort                            | `vector.c / vector_count_sort()`                    | ``O(N)``              | ``O(max - min)``  |
| Merge sort                            | `vector.c / vector_merge_sort()`                    | ``O(N*log N)``        | ``O(N)``          |
| Generate all permutations             | `vector.c / vector_print_permutations()`            | ``O(N!*N)``           | ``O(N)``          |
| Check if sorted                       | `vector.c / vector_is_sorted()`                     | ``O(N)``              | ``O(1)``          |
| Binary search (lower bound)           | `vector.c / vector_lower_bound()`                   | ``O(log N)``          | ``O(1)``          |
| Binary search (upper bound)           | `vector.c / vector_upper_bound()`                   | ``O(log N)``          | ``O(1)``          |
| Size of LCS                           | `vector.c / vector_size_of_largest_subsequence()`   | ``O(F*S)``            | ``O(F*S)``        |

### Structures

| Interface        | Structure                 | Name      | Source file       | Description                           |
| ---------------- | ------------------------- | --------- | ----------------- | ------------------------------------- |
| List             | Vector                    | `vector`  | `vector.c`        | dynamic array of integers             |
| List             | Doubly-linked list        | `list`    | `list.c`          | doubly-linked list of integers        |
| Stack            | ArrayStack                | `stack`   | `queue.c`         | stack on array                        |
| Queue            | ArrayQueue                | `queue`   | `queue.c`         | FIFO queue on array                   |
| Deque            | ArrayDeque                | `deque`   | `queue.c`         | Deque on array                        |
|                  | String                    | `string`  | `string.c`        | dynamic ASCII string                  |
| Set              | Naive set                 | `set`     | `set.c`           | set based on integer vector           |
| Set              | Chained set               | `chset`   | `set.c`           | chained hash table                    |

### Operations

| Operation         | vector   | list     | set         | stack     | queue     | deque    |
| ----------------- | -------- | -------- | ----------- | --------- | --------- | -------- |
| `push_front(v)`   | ``O(N)`` | ``O(1)`` |             |           |           | ``O(1)`` |
| `pop_front(v)`    |          | ``O(1)`` |             |           | ``O(1)``  | ``O(1)`` |
| `push_back(v)`    | ``O(1)`` | ``O(1)`` |             | ``O(1)``  | ``O(1)``  | ``O(1)`` |
| `pop_back(v)`     | ``O(1)`` | ``O(1)`` |             | ``O(1)``  |           | ``O(1)`` |
| `get(i)`          | ``O(1)`` | ``O(N)`` |             |           |           |          |
| `remove(i)`       |          | ``O(1)`` |             |           |           |          |
| `insert(i,v)`     | ``O(N)`` | ``O(1)`` |             |           |           |          |
| `remove(v)`       |          |          | ``O(N)``    |           |           |          |
| `insert(v)`       |          |          | ``O(N)``    |           |           |          |
| `contains(v)`     | ``O(N)`` | ``O(N)`` | ``O(logN)`` |           |           |          |

### TODO 
 * Sync: Mutex, RwLock
 * HashSet, Singly-Linked list (lock-free version)
 * Parallel algorithms: reduce, scan
 * Quicksort, heapsort, shunting yard, queadtree
 * HTTP server

### Literature
 * "Open Data Structures" by Pat Morin

