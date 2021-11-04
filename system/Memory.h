/*
 * The most primitive implementation of memory allocator which is painfully slow.
 * allocate() and free() have O(N) time complexity.
 */
#pragma once
#include <iostream>
#include <unistd.h>
using namespace std;

struct Block {
  size_t size;
  Block* next;
  bool free;
};

static Block* fblock = nullptr;
static Block* lblock = nullptr;

/**
 * Allocates new region of memory for particular object
 *
 * @tparam T - type of the value
 * @return pointer to the allocated region
 */
template <class T>
T* allocate() {
  const auto size = sizeof(T);

  if (fblock == nullptr) {
    cout << "Allocating first block. size = " << sizeof(size) << endl;
    fblock = (Block*)sbrk(sizeof(Block) + size);
    fblock->size = size;
    fblock->next = nullptr;
    fblock->free = false;
    lblock = fblock;
    return (T*)(((char*)fblock) + sizeof(Block));
  }

  Block* current = fblock;
  while (current->next != nullptr) {
    current = current->next;
    if (current->free && current->size >= size) { break; }
  }

  if (lblock == current) {
    cout << "Allocating a new block. size = " << sizeof(size) << endl;
    Block* nblock = (Block*)sbrk(sizeof(Block) + size);
    nblock->size = size;
    nblock->next = nullptr;
    nblock->free = false;
    current->next = nblock;
    lblock = nblock;
    return (T*)(((char*)nblock) + sizeof(Block));
  }

  cout << "Found free block. size = " << sizeof(current->size) << endl;
  current->free = false;
  return (T*)(((char*)current) + sizeof(Block));
}

/**
 * Frees memory that was used by this object
 *
 * @param ptr - pointer to allocated region
 */
void deallocate(void* const ptr) {
  Block* block = (Block*)(((char*)ptr) - sizeof(Block));
  block->free = true;
}
