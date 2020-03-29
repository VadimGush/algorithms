#include "set.c"

void check(const struct vector* this) {
  if (vector_is_sorted(this))
    printf("Vector is sorted!\n");
  else
    printf("Vector is not sorted ;C\n");
}

int main() {

  struct vector data = vector_create();
  // vector_push_array(&data, elements, 6);
  struct naive_set set = {data};
  set_print(&set);
  set_insert(&set, 2);
  set_insert(&set, 4);
  set_insert(&set, -1);
  set_insert(&set, 3);
  set_insert(&set, 0);
  set_insert(&set, 1);
  set_insert(&set, 13);
  set_insert(&set, 2);
  set_insert(&set, 3);
  set_print(&set);
  set_remove(&set, -1);
  set_remove(&set, 13);
  set_print(&set);
  set_remove(&set, 1);
  set_remove(&set, 3);
  set_print(&set);
  set_insert(&set, 3);
  set_print(&set);

  return 0;
}
