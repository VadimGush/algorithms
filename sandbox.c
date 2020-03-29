#include "set.c"

void test_sort() {

}

int main() {

  struct vector first = vector_create();
  vector_push_back(&first, 5);
  vector_push_back(&first, 3);
  vector_push_back(&first, 4);
  vector_merge_sort(&first);
  vector_print(&first);

  struct vector second = vector_create();
  vector_push_back(&second, 3);
  vector_push_back(&second, 2);
  vector_merge_sort(&second);
  vector_print(&second);

  struct vector third = vector_create();
  int array[] = {6, 5, 4, 3, 2, 7, 1};
  vector_push_array(&third, array, 7);
  vector_merge_sort(&third);
  vector_print(&third);

  struct vector last = vector_create();
  vector_push_back(&last, 3);
  vector_merge_sort(&last);
  vector_print(&last);

  return 0;
}
