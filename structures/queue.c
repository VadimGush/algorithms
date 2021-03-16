#include <stdio.h>

#include "queue.h"
#include "vector.h"

struct stack stack_create() {
  struct stack result = {
    vector_create()
  };
  return result;
}

void stack_push(struct stack* this, int value) {
  vector_push_back(&this->data, value);
}

int stack_pop(struct stack* this) {
  int value = this->data.data[this->data.size - 1];
  vector_remove(&this->data, this->data.size - 1);
  return value;
}

size_t stack_size(struct stack* this) {
  return this->data.size;
}

struct queue queue_create() {
  struct queue result = {
    vector_create(),
    0,
    0
  };

  return result;
}

static void resize(struct queue* this) {
  struct vector old = this->data;
  struct vector new = vector_create_with_capacity(this->data.capacity * 2);

  size_t pos = 0;
  size_t head = this->head;
  size_t size = this->size;
  while (size > 0) {
    vector_push_back(&new, old.data[head]);
    pos += 1;
    head += 1;
    size -= 1;

    if (head >= old.size) {
      head = 0;
    }
  }

  this->head = 0;
  this->tail = this->size - 1;
  vector_delete(&old);
  this->data = new;
}

void queue_push_back(struct queue* this, int value) {
  if (this->size >= this->data.capacity) {
    resize(this);
  }

  if (this->size != 0)
    this->tail = (this->tail + 1) % this->data.capacity;

  if (this->tail >= this->data.size)
    vector_push_back(&this->data, value);
  else
    this->data.data[this->tail] = value;

  this->size += 1;
}

int queue_pop_front(struct queue* this) {
  // TODO: if this->size == 0 then return error
  // TODO: In case if capacity is too large and size is small, we want to
  //       reduce capacity in order to free some memory 
  int result = this->data.data[this->head];

  this->size -= 1;
  if (this->head != this->tail)
    this->head = (this->head + 1) % this->data.capacity;

  return result;
}

size_t queue_size(struct queue* this) {
  return this->size;
}

void queue_debug_print(struct queue* this) {
  // [3] [4] [5] [6] [ ] 
  //  h       t

  for (size_t i = 0; i < this->data.capacity; i++) {
    if (i >= this->data.size) {
      printf("[_] ");
      continue;
    }

    if (this->head < this->tail) {
      if (i >= this->head && i <= this->tail) {
        printf("[%d] ", this->data.data[i]);
      } else {
        printf("[ ] ");
      }
    } else if (this->head > this->tail) {
      if (i <= this->tail || i >= this->head) {
        printf("[%d] ", this->data.data[i]);
      } else {
        printf("[ ] ");
      }
    } else {
      if (i == this->head && this->size != 0) {
        printf("[%d] ", this->data.data[i]);
      } else {
        printf("[ ] ");
      }
    }
  }

  printf("\n");

  for (size_t i = 0; i < this->data.capacity; i++) {
    if (i == this->head && i == this->tail) {
      printf("th  ");
    } else if (i == this->head) {
      printf(" h  ");
    } else if (i == this->tail) {
      printf(" t  ");
    } else {
      printf("    ");
    }
  }

  printf("\n");
}

