# Multithreading

## Notes

 1. Any type of synchronisation slows down execution
 2. A lot of waiting (like reading from memory) decreases performance

## Parallel Algorithms

Some STL algorithm support parallel execution:
```c++
/**
 * execution::seq - sequnced
 * execution::par - parallel 
 * execution::par_unseq - parallel + vectorized (SIMD)
 * execution::unseq - vectorized
 */
sort(execution::par, begin(list), end(list));
```