![](https://github.com/vadimgush/algorithms/workflows/CMake/badge.svg)

# Algorithms and data structures

Implementation of different algorithms and data structures in C.

### Algorithms

| Algorithm                             | Source file / function name                         | Time complexity       | Space complexity  |
| ------------------------------------- | --------------------------------------------------- | --------------------- | ----------------- |
| Linear search                         | `Vector.c / vector_find()`                          | ``O(Node)``              |                   |
| Invert array                          | `Vector.c / vector_invert()`                        | ``O(Node)``              |                   |
| Cyclic shift of array to right/left   | `Vector.c / vector_shift_...()`                     | ``O(Node)``              |                   |
| Search in text                        | `string.c / string_find()`                          | ``O(Node*I)``            |                   |
| Insert sort                           | `Vector.c / vector_insert_sort()`                   | ``O(Node^2)``            | ``O(1)``          |
| Choice sort                           | `Vector.c / vector_choice_sort()`                   | ``O(Node^2)``            | ``O(1)``          |
| Bubble sort                           | `Vector.c / vector_bubble_sort()`                   | ``O(Node^2)``            | ``O(1)``          |
| Count sort                            | `Vector.c / vector_count_sort()`                    | ``O(Node)``              | ``O(max - min)``  |
| Merge sort                            | `Vector.c / vector_merge_sort()`                    | ``O(Node*log Node)``        | ``O(Node)``          |
| Generate all permutations             | `Vector.c / vector_print_permutations()`            | ``O(Node!*Node)``           | ``O(Node)``          |
| Check if sorted                       | `Vector.c / vector_is_sorted()`                     | ``O(Node)``              | ``O(1)``          |
| Binary search (lower bound)           | `Vector.c / vector_lower_bound()`                   | ``O(log Node)``          | ``O(1)``          |
| Binary search (upper bound)           | `Vector.c / vector_upper_bound()`                   | ``O(log Node)``          | ``O(1)``          |
| Size of LCS                           | `Vector.c / vector_size_of_largest_subsequence()`   | ``O(F*S)``            | ``O(F*S)``        |

### Structures

| Interface        | Structure                 | Name      | Source file       | Description                           |
| ---------------- | ------------------------- | --------- | ----------------- | ------------------------------------- |
| List             | Vector                    | `Vector`  | `Vector.c`        | dynamic array of integers             |
| List             | Doubly-linked DList        | `DList`    | `DList.c`          | doubly-linked DList of integers        |
| Stack            | ArrayStack                | `stack`   | `queue.c`         | stack on array                        |
| Queue            | ArrayDeque                | `queue`   | `queue.c`         | FIFO queue on array                   |
| Deque            | ArrayDeque                | `deque`   | `queue.c`         | Deque on array                        |
|                  | String                    | `string`  | `string.c`        | dynamic ASCII string                  |
| Set              | Naive set                 | `set`     | `set.c`           | set based on integer Vector           |
| Set              | Chained set               | `chset`   | `set.c`           | chained hash table                    |

### Operations

| Operation         | Vector   | DList     | set         | stack     | queue     | deque    |
| ----------------- | -------- | -------- | ----------- | --------- | --------- | -------- |
| `push_front(v)`   | ``O(Node)`` | ``O(1)`` |             |           |           | ``O(1)`` |
| `pop_front(v)`    |          | ``O(1)`` |             |           | ``O(1)``  | ``O(1)`` |
| `push_back(v)`    | ``O(1)`` | ``O(1)`` |             | ``O(1)``  | ``O(1)``  | ``O(1)`` |
| `pop_back(v)`     | ``O(1)`` | ``O(1)`` |             | ``O(1)``  |           | ``O(1)`` |
| `get(i)`          | ``O(1)`` | ``O(Node)`` |             |           |           |          |
| `remove(i)`       |          | ``O(1)`` |             |           |           |          |
| `insert(i,v)`     | ``O(Node)`` | ``O(1)`` |             |           |           |          |
| `remove(v)`       |          |          | ``O(Node)``    |           |           |          |
| `insert(v)`       |          |          | ``O(Node)``    |           |           |          |
| `contains(v)`     | ``O(Node)`` | ``O(Node)`` | ``O(logN)`` |           |           |          |

### TODO 
 * Sync: Mutex, RwLock
 * HashSet, Singly-Linked DList (lock-free version)
 * Parallel algorithms: reduce, scan
 * Quicksort, heapsort, shunting yard, queadtree
 * HTTP server

### Literature
 * "Open Data Structures" by Pat Morin

