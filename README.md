# Algorithms and data structures

Implementation of different algorithms and data structures in C.

### Sequential algorithms

| Algorithm                             | Source file / function name               | Time complexity       | Space complexity  |
| ------------------------------------- | ----------------------------------------- | --------------------- | ----------------- |
| Linear search                         | `vector.c / vector_find()`                | ``O(N)``              |                   |
| Invert array                          | `vector.c / vector_invert()`              | ``O(N)``              |                   |
| Eratosthenes sieve                    | `eratosthenes_sieve.c`                    | ``O(N*log(log N))``   |                   |
| Cyclic shift of array to right/left   | `vector.c / vector_shift_...()`           | ``O(N)``              |                   |
| Search in text                        | `string.c / string_find()`                | ``O(N*I)``            |                   |
| Insert sort                           | `vector.c / vector_insert_sort()`         | ``O(N^2)``            | ``O(1)``          |
| Choice sort                           | `vector.c / vector_choice_sort()`         | ``O(N^2)``            | ``O(1)``          |
| Bubble sort                           | `vector.c / vector_bubble_sort()`         | ``O(N^2)``            | ``O(1)``          |
| Count sort                            | `vector.c / vector_count_sort()`          | ``O(N)``              | ``O(max - min)``  |
| Merge sort                            | `vector.c / vector_merge_sort()`          | ``O(N*log N)``        | ``O(N)``          |
| Generate all permutations             | `vector.c / vector_print_permutations()`  | ``O(N!*N)``           | ``O(N)``          |
| Check if sorted                       | `vector.c / vector_is_sorted()`           | ``O(N)``              | ``O(1)``          |
| Binary search (lower bound)           | `vector.c / vector_lower_bound()`         | ``O(log N)``          | ``O(1)``          |
| Binary search (upper bound)           | `vector.c / vector_upper_bound()`         | ``O(log N)``          | ``O(1)``          |
| Size of LCS                           | `vector.c / vector_size_of_largest_subsequence()` | ``O(F*S)``    | ``O(F*S)``        |

**TODO:** Shunting yard, Quadtree

### Parallel algorithms

**TODO:** Reduce, scan.

### Structures

| Structure                 | Source file |
| ------------------------- | ----------- |
| Vector / dynamic array    | `vector.c`  |
| Doubly-linked list        | `list.c`    |
| String                    | `string.c`  |
| Naive set                 | `set.c`     |

**TODO:** HashSet, Singly-Linked list (Lock-free version)

### Sync primitives 

**TODO:** Mutex, RwLock

### System programming

**TODO:** Simple HTTP webserver on async sockets, TCP/UDP packets listener
