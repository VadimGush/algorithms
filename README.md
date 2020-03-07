# Algorithms and data structures

Implementation of different algorithms and data structures in C.

### Sequential algorithms

| Algorithm | Source file | Function name | Time complexity | Space complexity |
| --------- | ----------- | ------------- | --------------- | ---------------- |
| Linear search                         | `vector.c`                | `vector_find()`               | ``O(N)``              | |
| Invert array                          | `vector.c`                | `vector_invert()`             | ``O(N)``              | |
| Eratosthenes sieve                    | `eratosthenes_sieve.c`    |                               | ``O(N*log(log N))``   | |
| Cyclic shift of array to right/left   | `vector.c`                | `vector_shift_...()`          | ``O(N)``              | |
| Search in text                        | `string.c`                | `string_find()`               | ``O(N*I)``            | |
| Insert sort                           | `vector.c`                | `vector_insert_sort()`        | ``O(N^2)``            | ``O(1)``          |
| Choice sort                           | `vector.c`                | `vector_choice_sort()`        | ``O(N^2)``            | ``O(1)``          |
| Bubble sort                           | `vector.c`                | `vector_bubble_sort()`        | ``O(N^2)``            | ``O(1)``          |
| Count sort                            | `vector.c`                | `vector_count_sort()`         | ``O(N)``              | ``O(max - min)``  |
| Generate permutations                 | `vector.c`                | `vector_print_permutations()` | ``O(N!*N)``           | ``O(N)``          |

### Parallel algorithms

**TODO:** Reduce, scan.

### Structures

| Structure | Source file |
| --------- | ----------- |
| Vector or dynamic array | `vector.c` |
| Doubly-linked list | `list.c` |
| String | `string.c` |
