#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>

typedef enum {
  LL_OK = 0,         // success
  LL_ERR_NULL = -1,  // NULL pointer passed
  LL_ERR_EMPTY = -2, // list empty (e.g. pop on empty)
  LL_ERR_ALLOC = -3  // malloc() failed
} ll_status_t;

typedef struct linked_list linked_list_t;

linked_list_t* ll_create();
ll_status_t ll_push(linked_list_t* ll, int value);
ll_status_t ll_pop_head(linked_list_t* ll, int* value);
ll_status_t ll_peek_head(linked_list_t* ll, int* value);
ll_status_t ll_peek_tail(linked_list_t* ll, int* value);
void ll_clear(linked_list_t* ll);
void ll_free(linked_list_t* ll);

size_t ll_get_size(const linked_list_t* ll);
static inline int ll_is_empty(const linked_list_t* ll) {
  return ll_get_size(ll) == 0;
}

#endif // !LINKED_LIST_H
