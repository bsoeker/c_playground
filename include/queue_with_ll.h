#ifndef QUEUE_LL_H
#define QUEUE_LL_H

#include <stddef.h>

typedef struct queue_ll queue_ll_t;

typedef enum {
  queue_LL_OK = 0,         // success
  queue_LL_ERR_NULL = -1,  // NULL pointer passed
  queue_LL_ERR_EMPTY = -2, // queue empty
  queue_LL_ERR_ALLOC = -3  // malloc() failed
} queue_ll_status_t;

queue_ll_t* queue_ll_create();
queue_ll_status_t queue_ll_push(queue_ll_t* queue, int value);
queue_ll_status_t queue_ll_pop(queue_ll_t* queue, int* value);
queue_ll_status_t queue_ll_peak(queue_ll_t* queue, int* value);
void queue_ll_clear(queue_ll_t queue);
void queue_ll_free(queue_ll_t queue);

size_t queue_ll_get_size(queue_ll_t* queue);
static inline int queue_ll_is_empty(queue_ll_t* queue) {
  return queue_ll_get_size(queue) == 0;
}

#endif // !QUEUE_LL_H
