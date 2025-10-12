#include "queue_with_ll.h"
#include "doubly_linked_list.h"
#include <stdlib.h>

struct queue_ll {
  doubly_linked_list_t* list;
};

queue_ll_t* queue_ll_create() {
  queue_ll_t* queue = malloc(sizeof(*queue));
  if (!queue)
    return NULL;
  queue->list = d_ll_create();

  return queue;
}

queue_ll_status_t queue_ll_push(queue_ll_t* queue, int value) {
  d_ll_push_tail(queue->list, value);

  return queue_LL_OK;
}
queue_ll_status_t queue_ll_pop(queue_ll_t* queue, int* value) {
  d_ll_pop_head(queue->list, value);

  return queue_LL_OK;
}
queue_ll_status_t queue_ll_peak(queue_ll_t* queue, int* value) {
  d_ll_peek_tail(queue->list, value);

  return queue_LL_OK;
}
void queue_ll_clear(queue_ll_t queue) { d_ll_clear(queue.list); }
void queue_ll_free(queue_ll_t queue) { d_ll_free(queue.list); }

size_t queue_ll_get_size(queue_ll_t* queue) {
  return d_ll_get_size(queue->list);
}
