#include "doubly_linked_list.h"
#include <stdio.h>
#include <stdlib.h>

// clang-format off
#define D_LL_CHECK_PTR_RET(d_ll, retval)                                       \
  do {                                                                         \
    if (!(d_ll)) {                                                             \
      fprintf(stderr, "Linked list error: %s called with NULL\n", __func__);   \
      return (retval);                                                         \
    }                                                                          \
  } while (0)

#define D_LL_EXIT_IF_EMPTY(d_ll, retval)                                    \
  do {                                                                         \
    if (d_ll_is_empty(d_ll)) {                                                 \
      fprintf(stderr, "List is empty!\n");                                     \
      return (retval);                                                         \
    }                                                                          \
  } while (0)
// clang-format on

typedef struct node {
  int value;
  struct node* next;
  struct node* prev;
} node_t;

struct doubly_linked_list {
  size_t size;
  node_t* head;
  node_t* tail;
};

doubly_linked_list_t* d_ll_create() {
  doubly_linked_list_t* d_ll = malloc(sizeof(*d_ll));
  if (!d_ll)
    return NULL;

  d_ll->size = 0;
  d_ll->head = d_ll->tail = NULL;
  return d_ll;
}

// []
// [0 <=> 1 <=> 2]
d_ll_status_t d_ll_push_head(doubly_linked_list_t* d_ll, int value) {
  D_LL_CHECK_PTR_RET(d_ll, D_LL_ERR_NULL);

  node_t* new_node = malloc(sizeof(node_t));
  if (!new_node) {
    fprintf(stderr, "malloc() failed!\n");
    return D_LL_ERR_ALLOC;
  }

  new_node->value = value;
  new_node->next = NULL;
  new_node->prev = NULL;

  if (d_ll_is_empty(d_ll)) {
    d_ll->head = d_ll->tail = new_node;
  } else {
    new_node->next = d_ll->head;
    d_ll->head->prev = new_node;
    d_ll->head = new_node;
  }

  d_ll->size++;
  return D_LL_OK;
}

d_ll_status_t d_ll_push_tail(doubly_linked_list_t* d_ll, int value) {
  D_LL_CHECK_PTR_RET(d_ll, D_LL_ERR_NULL);

  node_t* new_node = malloc(sizeof(*new_node));
  if (!new_node) {
    fprintf(stderr, "malloc() failed!\n");
    return D_LL_ERR_ALLOC;
  }

  new_node->value = value;
  new_node->next = NULL;
  new_node->prev = NULL;

  if (d_ll_is_empty(d_ll)) {
    d_ll->head = d_ll->tail = new_node;
  } else {
    new_node->prev = d_ll->tail;
    d_ll->tail->next = new_node;
    d_ll->tail = new_node;
  }

  d_ll->size++;
  return D_LL_OK;
}

// [0 1]
d_ll_status_t d_ll_pop_head(doubly_linked_list_t* d_ll, int* value) {
  D_LL_CHECK_PTR_RET(d_ll, D_LL_ERR_NULL);
  D_LL_EXIT_IF_EMPTY(d_ll, D_LL_ERR_EMPTY);

  *value = d_ll->head->value;

  if (d_ll->head == d_ll->tail) {
    free(d_ll->head);
    d_ll->head = d_ll->tail = NULL;
  } else {
    d_ll->head = d_ll->head->next;
    free(d_ll->head->prev);
    d_ll->head->prev = NULL;
  }

  d_ll->size--;
  return D_LL_OK;
}
d_ll_status_t d_ll_pop_tail(doubly_linked_list_t* d_ll, int* value) {
  D_LL_CHECK_PTR_RET(d_ll, D_LL_ERR_NULL);
  D_LL_EXIT_IF_EMPTY(d_ll, D_LL_ERR_EMPTY);

  *value = d_ll->tail->value;

  if (d_ll->head == d_ll->tail) {
    free(d_ll->tail);
    d_ll->head = d_ll->tail = NULL;
  } else {
    d_ll->tail = d_ll->tail->prev;
    free(d_ll->tail->next);
    d_ll->tail->next = NULL;
  }

  d_ll->size--;
  return D_LL_OK;
}
d_ll_status_t d_ll_peek_head(const doubly_linked_list_t* d_ll, int* value) {
  D_LL_CHECK_PTR_RET(d_ll, D_LL_ERR_NULL);
  D_LL_EXIT_IF_EMPTY(d_ll, D_LL_ERR_EMPTY);

  *value = d_ll->head->value;
  return D_LL_OK;
}
d_ll_status_t d_ll_peek_tail(const doubly_linked_list_t* d_ll, int* value) {
  D_LL_CHECK_PTR_RET(d_ll, D_LL_ERR_NULL);
  D_LL_EXIT_IF_EMPTY(d_ll, D_LL_ERR_EMPTY);

  *value = d_ll->tail->value;
  return D_LL_OK;
}

void d_ll_clear(doubly_linked_list_t* d_ll) {
  node_t* cur = d_ll->head;

  while (cur) {
    node_t* next = cur->next;
    free(cur);
    cur = next;
  }

  d_ll->head = d_ll->tail = NULL;
  d_ll->size = 0;
}

void d_ll_free(doubly_linked_list_t* d_ll) {
  d_ll_clear(d_ll);
  free(d_ll);
}

size_t d_ll_get_size(const doubly_linked_list_t* d_ll) {
  return d_ll ? d_ll->size : 0;
}
