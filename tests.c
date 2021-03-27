#include <stdlib.h>
#include <stdio.h>

#include "test/test.h"

#include "structures/vector.h"
#include "structures/set.h"
#include "structures/string.h"
#include "structures/list.h"
#include "structures/queue.h"

void test_vector() {
  struct vector vector = vector_create();
  assert(0, vector.size);

  vector_push_back(&vector, 3);
  assert(1, vector.size);

  assert(3, vector.data[0])

  vector_push_back(&vector, 4);
  assert(2, vector.size);
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

  int removed_value = vector_pop_back(&vector);
  assert(4, removed_value);
  assert(2, vector.size);

  removed_value = vector_pop_back(&vector);
  assert(3, removed_value);
  assert(1, vector.size);

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

void test_binary_search() {
  const int sorted[] = {1, 2, 2, 3, 6, 6, 7};
  struct vector vector = vector_create();
  vector_push_array(&vector, sorted, 7);

  assert(0, vector_lower_bound(&vector, -2))
  assert(0, vector_lower_bound(&vector, 0))
  assert(0, vector_lower_bound(&vector, 1))
  assert(1, vector_lower_bound(&vector, 2))
  assert(3, vector_lower_bound(&vector, 3))
  assert(4, vector_lower_bound(&vector, 4))
  assert(4, vector_lower_bound(&vector, 5))
  assert(4, vector_lower_bound(&vector, 6))
  assert(6, vector_lower_bound(&vector, 7))
  assert(7, vector_lower_bound(&vector, 8))
  assert(7, vector_lower_bound(&vector, 10))

  assert(0, vector_upper_bound(&vector, -5))
  assert(1,vector_upper_bound(&vector, 1))
  assert(3, vector_upper_bound(&vector, 2))
  assert(4, vector_upper_bound(&vector, 4))
  assert(4, vector_upper_bound(&vector, 5))
  assert(7, vector_upper_bound(&vector, 7))
  assert(7, vector_upper_bound(&vector, 10))

  assert(4, vector_find_first(&vector, 6))
  assert(5, vector_find_last(&vector, 6))
  assert(7, vector_find_first(&vector, 4))
  assert(7, vector_find_last(&vector, 4))
  assert(7, vector_find_first(&vector, -1))
  assert(7, vector_find_last(&vector, -1))

  passed()
}

void test_size_lseq() {

  {
    int array[] = {1, 3, 7, 9, 0, 4, 11};
    struct vector first = vector_create();
    vector_push_array(&first, array, 7);

    int other[] = {1, 7, 11};
    struct vector second = vector_create();
    vector_push_array(&second, other, 3);

    int result = vector_size_of_largest_subsequence(&first, &second);
    assert(3, result);
  }

  {
    int array[] = {1, 3, 4, 6};
    struct vector first = vector_create();
    vector_push_array(&first, array, 4);

    int other[] = {1, 7, 11, 0, -1, 3, 6, 7, 7, 4};
    struct vector second = vector_create();
    vector_push_array(&second, other, 10);

    int result = vector_size_of_largest_subsequence(&first, &second);
    assert(3, result);
  }

  passed();
}

void test_string() {
  struct string string = string_create();
  assert(1, string.size); // because of zero character at the end
  assert(0, string_len(&string));

  string_append(&string, "Hello world!", 12);
  assert_true(compare_str("Hello world!", string.data));
  assert(12, string_len(&string));

  string_append(&string, "!!", 2);
  assert_true(compare_str("Hello world!!!", string.data));

  assert(6, string_find(&string, "world", 5));
  assert(-1, string_find(&string, "milk", 4));

  struct string tofind = string_create();
  string_append(&tofind, "world", 5);
  assert(6, string_find_string(&string, &tofind));

  passed();
}

void test_list() {
  struct list list = list_create();
  list_push_back(&list, 4);
  list_push_front(&list, 5);

  assert(5, list_get(&list, 0)->value);
  assert(4, list_get(&list, 1)->value);
  assert(2, list.size);

  list_insert_after(&list, list.first, 7);
  list_insert_before(&list, list.last, 8);

  assert(7, list_get(&list, 1)->value);
  assert(8, list_get(&list, 2)->value);
  assert(4, list.size);

  list_pop_front(&list);

  assert(7, list_get(&list, 0)->value);
  assert(3, list.size);

  list_pop_back(&list);

  assert(8, list_get(&list, 1)->value);
  assert(2, list.size);

  passed();
}

void test_stack() {
  struct stack stack = stack_create();

  stack_push(&stack, 3);
  stack_push(&stack, 4);

  assert(2, stack_size(&stack));

  assert(4, stack_pop(&stack));
  assert(1, stack_size(&stack));

  stack_push(&stack, 7);
  
  assert(7, stack_pop(&stack));
  assert(1, stack_size(&stack));

  assert(3, stack_pop(&stack));
  assert(0, stack_size(&stack));


  passed();
}

void test_queue() {
  struct queue queue = queue_create();

  queue_push_back(&queue, 3);
  queue_push_back(&queue, 5);
  queue_push_back(&queue, 7);
  queue_push_back(&queue, 8);
  assert(4, queue_size(&queue));
  // 3 5 7 8

  assert(3, queue_pop_front(&queue));
  assert(3, queue_size(&queue));
  // 5 7 8

  queue_push_back(&queue, 9);
  assert(4, queue_size(&queue));
  // 5 7 8 9

  assert(5, queue_pop_front(&queue));
  assert(3, queue_size(&queue));
  // 7 8 9

  queue_push_back(&queue, 6);
  assert(4, queue_size(&queue));
  // 7 8 9 6

  passed();
}

void test_queue2() {
  struct queue queue = queue_create();

  queue_push_back(&queue, 3);
  queue_push_back(&queue, 5);
  queue_push_back(&queue, 7);
  queue_push_back(&queue, 8);
  assert(4, queue_size(&queue));
  // 3 5 7 8 
  
  assert(3, queue_pop_front(&queue));
  assert(5, queue_pop_front(&queue));
  assert(7, queue_pop_front(&queue));
  assert(1, queue_size(&queue));
  // 8

  queue_push_back(&queue, 4);
  queue_push_back(&queue, 5);
  assert(3, queue_size(&queue));
  // 8 4 5

  assert(8, queue_pop_front(&queue));
  assert(2, queue_size(&queue));
  // 4 5

  assert(4, queue_pop_front(&queue));
  assert(1, queue_size(&queue));
  // 5

  passed();
}

void run_tests() {
  test_vector();
  test_set();
  test_sort();
  test_binary_search();
  test_size_lseq();
  test_string();
  test_list();
  test_stack();
  test_queue();
  test_queue2();

  result();
}

int main() {
  run_tests();

  return 0;
}
