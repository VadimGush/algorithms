#include "vector.c"
#include "list.c"
#include "string.c"

int main() {
  struct vector v = vector_create();
  vector_push(&v, 5);
  vector_push(&v, 1);
  vector_push(&v, 3);
  vector_push(&v, 2);
  vector_push(&v, 4);
  vector_print(&v);

  vector_bubble_sort(&v);
  vector_print(&v);

  return 0;
}
