/*
 * The most primitive implementation of memory allocator which is painfully slow and insufficient
 * malloc() and free() have O(N) time complexity.
 */
#pragma once
#include <iostream>
#include <unistd.h>
using namespace std;

namespace Memory {

  /*
   * Memory layout looks like this
   *
   * <- ------------ REGION 1 -------------- ->       <- ---------- REGION N ----------- ->
   * |----------------------------------------|       |-----------------------------------|
   * | header    |           ...              |  ...  | header  |           ...           |
   * |----------------------------------------|       |-----------------------------------|
   * ^ header*                                                                             ^ program break
   *
   */

  /**
   * Represents header for specific region of memory
   */
  struct Header {
    Header* next; // pointer to the next region
    bool free; // is this region of memory is free or not
  };

  constexpr size_t region_size = 1024;
  static Header* control = nullptr;

  /**
   * Allocates a new region of memory of a particular size on the heap.
   *
   * @param size - required size
   * @return pointer to the newly allocated region
   */
  void* malloc(const size_t size) {
    // find region with enough space
    Header* current = control;
    Header* last = nullptr;
    while (current != nullptr) {
      // TODO: Reuse free space within a region
      if (current->free) {
        // Calculate how much memory is available within this region
        auto* const next = current->next == nullptr ? (char*)sbrk(0) : (char*)current->next;
        const size_t memory = ((char*)next - (char*)current) - sizeof(Header);

        // If it's enough to fit our object, then just use it
        if (memory >= size) {
          current->free = false;
          return (char*)current + sizeof(Header);
        }
      }
      last = current;
      current = current->next;
    }

    // create a new region
    const size_t regions = ((size + sizeof(Header)) - 1) / region_size + 1;
    auto* const header = (Header*)sbrk((int)(regions * region_size));
    if (last != nullptr) { last->next = header; }
    header->next = nullptr;
    header->free = false;

    if (control == nullptr) { control = header; }

    return (char*)header + sizeof(Header);
  }

  /**
   * Frees memory that was used by this object
   *
   * @param ptr - pointer to allocated region
   */
  void free(void* const ptr) {
    auto* const block = (Header*)(((char*)ptr) - sizeof(Header));
    block->free = true;
  }

}
