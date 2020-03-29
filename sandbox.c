#include "set.c"
#include "test.h"

void test_vector() {
  struct vector vector = vector_create();
  assert(0, vector.size)
  vector_push_back(&vector, 3);
  assert(1, vector.size)
  assert(3, vector.data[0])
  vector_push_back(&vector, 4);
  assert(2, vector.size)
  assert(4, vector.data[1])
  vector_push_back(&vector, 2);
  vector_push_back(&vector, 1);
  int array[] = {3, 4, 2, 1};
  assert_true(array_equals(array, vector.data, vector.size))
  int sorted[] = {1, 2, 3, 4};
  vector_merge_sort(&vector);
  assert_true(array_equals(sorted, vector.data, vector.size))
  vector_remove(&vector, 1);
  int removed[] = {1, 3, 4};
  assert_true(array_equals(removed, vector.data, vector.size))
  assert(3, vector.size)

  passed()
}

void test_sort() {
  const int random[] = {3, 4, 2, 1, 5};
  const int sorted[] = {1, 2, 3, 4, 5};
  struct vector vector = vector_create();
  vector_push_array(&vector, random, 5);

  vector_bubble_sort(&vector);
  assert_true(array_equals(sorted, vector.data, vector.size))
  vector_clear(&vector);

  vector_push_array(&vector, random, 5);
  vector_choice_sort(&vector);
  assert_true(array_equals(sorted, vector.data, vector.size))
  vector_clear(&vector);

  vector_push_array(&vector, random, 5);
  vector_insert_sort(&vector);
  assert_true(array_equals(sorted, vector.data, vector.size))
  vector_clear(&vector);

  vector_push_array(&vector, random, 5);
  vector_merge_sort(&vector);
  assert_true(array_equals(sorted, vector.data, vector.size));
  vector_clear(&vector);

  passed();
}

void test_set() {
  struct naive_set set = set_create();
  assert(0, set_size(&set))
  set_insert(&set, 3);
  assert(1, set_size(&set))
  assert_true(set_contains(&set, 3))
  set_insert(&set, 3);
  assert(1, set_size(&set))
  set_insert(&set, 4);
  set_insert(&set, 1);
  assert(3, set_size(&set))
  assert_true(set_contains(&set, 3))
  assert_true(set_contains(&set, 4))
  assert_true(set_contains(&set, 1))
  set_remove(&set, 3);
  assert(2, set_size(&set))
  assert_true(set_contains(&set, 4))
  assert_true(set_contains(&set, 1))
  assert_false(set_contains(&set, 3))
  set_remove(&set, 1);
  set_remove(&set, 4);
  assert_true(set_empty(&set))
  assert_false(set_contains(&set, 4))
  assert_false(set_contains(&set, 1))
  passed()
}

void test_framework() {
  test_vector();
  test_set();
  test_sort();
  result();
}

int main() {
  test_framework();


  return 0;
}
