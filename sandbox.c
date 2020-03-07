#include "vector.c"
#include "list.c"
#include "string.c"

int main() {

  struct vector numbers = vector_create();
  vector_push(&numbers, 3);
  vector_push(&numbers, 0);
  vector_push(&numbers, 1);

  vector_print_permutations(&numbers);

  return 0;
}
