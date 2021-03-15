#pragma once
#include "stdbool.h"

struct node {
  struct node* prev;
  struct node* next;
  int value;
};

/**
 * Doubly linked list
 */
struct list {
  struct node* first;
  struct node* last;
  int size;
};

/**
 * Creates empty list
 *
 * @return new list
 */
struct list list_create();

/**
 * Initializes given list
 */
void list_init(struct list* list);

/**
 * Inserts an element at the back of the list
 * Time complexity: O(1)
 *
 * @param list list
 * @param value value of element
 */
void list_push_back(struct list* list, int value);

/**
 * Inserts an element at the front of the list
 * Time complexity: O(1)
 *
 * @param list list
 * @param value value of element
 */
void list_push_front(struct list* list, int value);

/**
 * Inserts element after this node and returns new node
 * Time complexity: O(1)
 *
 * @param list list
 * @param node current node
 * @param value value of new node
 * @return pointer to new node
 */
struct node* list_insert_after(struct list* list, struct node* node, int value);

/**
 * Finds element in the list
 * Time complexity: O(N)
 *
 * @param list list
 * @param element element to find
 * @return true if found otherwise false
 */
bool list_contains(struct list* list, int element);

/**
 * Inserts element before this node and returns new node
 * Time complexity: O(1)
 *
 * @param list list
 * @param node current node
 * @param value value of new node
 * @return pointer to the new node
 */
struct node* list_insert_before(struct list* list, struct node* node, int value);

/**
 * Removes element from the list and returns next node
 * Time complexity: O(1)
 *
 * @param list list
 * @param node node to delete
 * @return pointer to next node after deleted
 */
struct node* list_remove(struct list* list, struct node* node);

/**
 * Removes last element from the list
 * Time complexity: O(1)
 *
 * @param list list
 */
void list_pop_back(struct list* list);

/**
 * Removes first element from the list
 * Time complexity: O(1)
 *
 * @param list list
 */
void list_pop_front(struct list* list);

/**
 * Get node by index
 * If node doesn't exists then returns NULL
 * Time complexity: O(N)
 *
 * @param list list
 * @param index index
 * @return pointer to the node with given index
 */
struct node* list_get(struct list* list, int index);

/**
 * Prints list
 */
void list_print(struct list* list);

/**
 * Prints list in reverse order
 */
void list_print_reverse(struct list* list);
