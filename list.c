#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

void list_init(struct list* list) {
  list->first = NULL;
  list->last = NULL;
  list->size = 0;
}

struct list list_create() {
  struct list result;
  result.first = NULL;
  result.last = NULL;
  result.size = 0;
  return result;
}

/**
 * Creates new node
 *
 * @param next next node
 * @param prev previous node
 * @param value value of current node
 * @return new node with given value
 */
struct node* node_create(struct node* next, struct node* prev, int value) {
  struct node* result = malloc(sizeof(struct node));
  result->next = next;
  result->prev = prev;
  result->value = value;
  return result;
}

void list_push_back(struct list* list, int value) {
  // if list is empty
  if (list->first == NULL && list->first == list->last) {
    struct node* node = node_create(NULL, NULL, value);
    list->first = node;
    list->last = node;
  } else {
    struct node* prev_node = list->last;
    struct node* next_node = node_create(NULL, prev_node, value);
    prev_node->next = next_node;
    list->last = next_node;
  }

  list->size += 1;
}

void list_push_front(struct list* list, int value) {
  // if list is empty
  if (list->first == NULL && list->first == list->last) {
    struct node* node = node_create(NULL, NULL, value);
    list->first = node;
    list->last = node;
  } else {
    struct node* prev_node = node_create(list->first, NULL, value);
    struct node* next_node = list->first;
    next_node->prev = prev_node;
    list->first = prev_node;
  }

  list->size += 1;
}

struct node* list_insert_after(struct list* list, struct node* node, int value) {
  struct node* new_node = node_create(node->next, node, value);
  if (node->next != NULL) {
    struct node* next_node = node->next;
    next_node->prev = new_node;
  }
  node->next = new_node;

  if (node == list->last) {
    list->last = new_node;
  }

  list->size += 1;
  return new_node;
}

bool list_contains(struct list* list, int element) {
  struct node* current = list->first;
  while (current != NULL) {
    if (current->value == element) return true;
    current = current->next;
  }
  return false;
}

struct node* list_insert_before(struct list* list, struct node* node, int value) {
  struct node* new_node = node_create(node, node->prev, value);
  if (new_node->prev != NULL) {
    struct node* prev_node = new_node->prev;
    prev_node->next = new_node;
  }
  node->prev = new_node;

  if (node == list->first) {
    list->first = new_node;
  }

  list->size += 1;
  return new_node;
}

struct node* list_remove(struct list* list, struct node* node) {
  struct node* prev_node = node->prev;
  struct node* next_node = node->next;

  if (prev_node != NULL) {
    prev_node->next = next_node;
  }
  if (next_node != NULL) {
    next_node->prev = prev_node;
  }

  if (node == list->first) {
    list->first = next_node;
  }

  if (node == list->last) {
    list->last = prev_node;
  }

  list->size -= 1;
  free(node);
  return next_node;
}

void list_pop_back(struct list* list) {
  list_remove(list, list->last);
}

void list_pop_front(struct list* list) {
  list_remove(list, list->first);
}

struct node* list_get(struct list* list, int index) {
  struct node* current = list->first;
  for (int i = 1; i <= index; ++i) {
    if (current == NULL) return NULL;
    current = current->next;
  }
  return current;
}

/**
 * Returns node after N steps
 * or returns NULL if node doesn't exist
 * Time complexity: O(N)
 *
 * @param node node
 * @param steps number of steps
 * @return pointer to the node
 */
struct node* node_step(struct node* node, int steps) {
  struct node* current = node;
  for (int i = 1; i <= steps; ++i) {
    if (current == NULL) return NULL;
    current = current->next;
  }
  return current;
}

/**
 * Returns node after N steps backwards
 * or returns NULL if node doesn't exist
 * Time complexity: O(N)
 *
 * @param node node
 * @param steps number of steps
 * @return pointer to the node
 */
struct node* node_step_backwards(struct node* node, int steps) {
  struct node* current = node;
  for (int i = 1; i <= steps; ++i) {
    if (current == NULL) return NULL;
    current = current->prev;
  }
  return current;
}

void list_print(struct list* list) {
  printf("[ ");
  struct node* current = list->first;
  while (current != NULL) {
    printf("%d ", current->value);
    current = current->next;
  }
  printf("]\n");
}

void list_print_reverse(struct list* list) {
  printf("[ ");
  struct node *current = list->last;
  while (current != NULL) {
    printf("%d ", current->value);
    current = current->prev;
  }
  printf("] reverse order\n");
}
