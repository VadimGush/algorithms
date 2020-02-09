#include <stdio.h>
#include <stdlib.h>
#define INITIAL_CAPACITY 4

struct vector {
  int* data;
  int size;
  int capacity;
};

/**
 * Creates vector with given capacity
 */
struct vector vector_create_with_capacity(int capacity) {
  struct vector result;
  
  result.capacity = capacity;
  result.size = 0;
  result.data = malloc(result.capacity * sizeof(int));

  return result;
}

/**
 * Creates vector
 */
struct vector vector_create() {
  return vector_create_with_capacity(INITIAL_CAPACITY);
}

/**
 * Inserts an element at the back of the vector
 * Time complexity: O(1)
 */
void vector_push(struct vector* vec, int element) {
  if (vec->size == vec->capacity) {
    int* temp = malloc(vec->capacity * 2 * sizeof(int));
    for (int i = 0; i < vec->capacity; i++) {
      temp[i] = vec->data[i];
    }
    free(vec->data);
    vec->data = temp;
    vec->capacity *= 2;
  }

  vec->data[vec->size] = element;
  vec->size++;
}

/**
 * Removes last element from the back of the vector
 * Time complexity: O(1)
 */
void vector_pop(struct vector* vec) {
  if (vec->size > 0) {
    vec->size--;
  }
}

void print_vector(struct vector* vec) {
  printf("[ ");
  for (int i = 0; i < vec->size; ++i) {
    printf("%d ", vec->data[i]);
  }
  printf("] siz = %d, cap = %d\n", vec->size, vec->capacity);
}

int main(void) {

  struct vector v = vector_create();
  print_vector(&v);
  vector_push(&v, 5);
  vector_push(&v, 3);
  print_vector(&v);
  
  vector_push(&v, 10);
  vector_push(&v, 13);
  print_vector(&v);

  vector_push(&v, -47);
  print_vector(&v);

  vector_pop(&v);
  print_vector(&v);

  return 0;
}
