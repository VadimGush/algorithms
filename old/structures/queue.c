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
  return vector_pop_back(&this->data);
}

size_t stack_size(struct stack* this) {
  return this->data.size;
}

static void queue_resize(struct queue* const this, const size_t capacity) {
  struct vector old = this->data;
  struct vector new = vector_create_with_capacity(capacity);

  size_t head = this->head;
  size_t size = this->size;
  while (size > 0 && (this->size - size) < capacity) {
    new.data[this->size - size] = old.data[head];
    head += 1;
    size -= 1;

    // go the beginning of the array
    if (head >= old.capacity) {
      head = 0;
    }
  }

  this->head = 0;
  this->tail = this->size - 1;
  vector_delete(&old);
  this->data = new;
}

struct queue queue_create() {
  struct queue result = {
    vector_create(),
    0,
    0,
    0
  };

  return result;
}


void queue_push_back(struct queue* this, int value) {
  if (this->size >= this->data.capacity) {
    queue_resize(this, this->data.capacity * 2);
  }

  if (this->size != 0)
    this->tail = (this->tail + 1) % this->data.capacity;

  this->data.data[this->tail] = value;
  this->size += 1;
}

int queue_pop_front(struct queue* this) {
  int result = this->data.data[this->head];

  this->size -= 1;
  if (this->head != this->tail)
    this->head = (this->head + 1) % this->data.capacity;

  if (this->data.capacity > (3 * this->size)) {
    queue_resize(this, this->data.capacity / 2);
  }

  return result;
}

size_t queue_size(struct queue* this) {
  return this->size;
}

void queue_debug_print(struct queue* this) {
  // [3] [4] [5] [6] [ ] 
  //  h       t

  for (size_t i = 0; i < this->data.capacity; i++) {

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

struct deque deque_create() {
  struct deque result = {
    vector_create_with_capacity(4),
    0, 
    0, 
    0
  };

  return result;
}

void deque_push_back(struct deque* this, int value) {
  queue_push_back((struct queue*)this, value);
}

int dequeu_pop_back(struct deque* this) {
  int result = 0;

  if (this->size != 0) {
    result = this->data.data[this->tail];

    if (this->tail == 0)
      this->tail = this->data.capacity - 1;
    else 
      this->tail -= 1;

    this->size -= 1;
  }

  return result;
}

int deque_pop_front(struct deque* this) {
  return queue_pop_front((struct queue*)this);
}

void deque_push_front(struct deque* this, int value) {
  if (this->size >= this->data.capacity) {
    queue_resize((struct queue*)this, this->data.capacity * 2);
  }

  if (this->head == 0)
    this->head = this->data.capacity - 1;
  else 
    this->head -= 1;

  this->data.data[this->head] = value;
  this->size += 1;
}

void deque_debug_print(struct deque* this) {
  queue_debug_print((struct queue*)this);
}




