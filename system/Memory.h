/*
 * The most primitive implementation of memory allocator which is painfully slow.
 * allocate() and free() have O(N) time complexity.
 */
#pragma once
#include <iostream>
#include <unistd.h>
using namespace std;

constexpr size_t max_allocs = 100;

struct Block {
  void* pointer = nullptr;
  bool free = true;
  size_t size = 0;
};

// Pointers that we will store
Block blocks[max_allocs] = {};

/**
 * Allocates new region of memory for particular object
 *
 * @tparam T - type of the value
 * @return pointer to the allocated region
 */
template <class T>
T* allocate() {
  const size_t size = sizeof(T);

  Block* free = nullptr;
  for (auto& block : blocks) {
    if (block.pointer == nullptr || block.free) {
      if (block.size >= size || block.size == 0) {
        free = &block;
        break;
      }
    }
  }

  if (free == nullptr) {
    cout << "No more memory available";
    return nullptr;
  }

  if (free->pointer == nullptr) {
    cout << "[alloc] Allocated new region of size=" << size << endl;
    free->pointer = sbrk(size);
    free->size = size;
    free->free = false;
  } else {
    cout << "[alloc] Reused region at " << free->pointer << endl;
    free->free = false;
  }
  cout << "[alloc] Free region at " << free->pointer << " size=" << free->size << endl;

  return (T*)free->pointer;
}


/**
 * Frees memory that was used by this object
 *
 * @param pointer - pointer to allocated region
 */
void deallocate(void* const pointer) {
  for (auto& block : blocks) {
    if (block.pointer == pointer) {
      cout << "[free] Deallocated region at " << block.pointer << " size=" << block.size << endl;
      block.free = true;
      return;
    }
  }
  cout << "[free] Invalid pointer" << endl;
}
