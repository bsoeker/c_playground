#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>

typedef struct {
  int* data;
  size_t size;
  size_t cap;
  size_t front;
  size_t end;
} queue_t;

queue_t* queue_create(size_t cap);
void queue_enqueue(queue_t* q, int value);
int queue_dequeue(queue_t* q);
void queue_free(queue_t* q);
static inline int queue_is_empty(queue_t* q) { return q->size == 0; }
static inline int queue_get_size(queue_t* q) { return q->size; }

#endif // !QUEUE_H
