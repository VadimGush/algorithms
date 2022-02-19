
# Memory structure

```
                 |- --------------------------- -|
                 | Kernel                        |
                 | mapped into process virtual   |
                 | memory, but not accessible    |
     0xC00000000 |- --------------------------- -|
                 | argv, environ                 |
                 |- --------------------------- -|
                 | Stack                         |
                 | (grows down)                  |
    Top of stack |- - - - - - - - - - - - - - - -|
                 | Unallocated memory            |
                 |                               |
                 |                               |
                 |                               |
         Program |- - - - - - - - - - - - - - - -|
          break  | Heap (grows upwards)          |
                 |                               |
                 |- --------------------------- -| <- end
                 | Uninitialized data (bss)      |
                 |- --------------------------- -| <- edata
                 | Initialized data              |
                 |- --------------------------- -| <- text
                 | Text (program code)           |
                 |- --------------------------- -|
                 |                               |
      0x00000000 |- --------------------------- -|
```


## Memory management

 * `malloc()` - allocate block of memory
 * `free()` - free block of memory
 * `calloc()` - allocate an array
 * `realloc()` - resize existing block of memory
 * `memalign()` / `posix_memalign()` - allocating at aligned positions
 * `alloca()` - allocate memory on the stack

## Troubleshooting

 * `mtrace()`
 * `muntrace()`
 * `mcheck()`
 * `mprobe()`
 * `MALLOC_CHECK_`
