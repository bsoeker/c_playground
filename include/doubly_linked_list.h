#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stddef.h>

typedef enum {
  D_LL_OK = 0,         // success
  D_LL_ERR_NULL = -1,  // NULL pointer passed
  D_LL_ERR_EMPTY = -2, // list empty
  D_LL_ERR_ALLOC = -3  // malloc() failed
} d_ll_status_t;

typedef struct doubly_linked_list doubly_linked_list_t;

doubly_linked_list_t* d_ll_create();
d_ll_status_t d_ll_push_head(doubly_linked_list_t* d_ll, int value);
d_ll_status_t d_ll_push_tail(doubly_linked_list_t* d_ll, int value);
d_ll_status_t d_ll_pop_head(doubly_linked_list_t* d_ll, int* value);
d_ll_status_t d_ll_pop_tail(doubly_linked_list_t* d_ll, int* value);
d_ll_status_t d_ll_peek_head(const doubly_linked_list_t* d_ll, int* value);
d_ll_status_t d_ll_peek_tail(const doubly_linked_list_t* d_ll, int* value);

void d_ll_clear(doubly_linked_list_t* d_ll);
void d_ll_free(doubly_linked_list_t* d_ll);

size_t d_ll_get_size(const doubly_linked_list_t* d_ll);
static inline int d_ll_is_empty(const doubly_linked_list_t* d_ll) {
  return d_ll_get_size(d_ll) == 0;
}

#endif // !DOUBLY_LINKED_LIST_H
