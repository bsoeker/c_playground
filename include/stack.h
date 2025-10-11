#ifndef STACK_H
#define STACK_H

#include <stddef.h>
#include <stdlib.h>

typedef struct {
  int* data;
  size_t size;
  size_t cap;

} stack_t;

stack_t* stack_create(size_t cap);
void stack_push(stack_t* s, int value);
int stack_pop(stack_t* s);
void stack_free(stack_t* s);
static inline int stack_get_size(stack_t* s) { return s->size; };
static inline int stack_is_empty(stack_t* s) { return s->size == 0; }

#endif // STACK_H
