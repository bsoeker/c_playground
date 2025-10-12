#ifndef STACK_LL_H
#define STACK_LL_H

#include <stddef.h>

typedef struct stack_ll stack_ll_t;

typedef enum {
  STACK_LL_OK = 0,         // success
  STACK_LL_ERR_NULL = -1,  // NULL pointer passed
  STACK_LL_ERR_EMPTY = -2, // stack empty
  STACK_LL_ERR_ALLOC = -3  // malloc() failed
} stack_ll_status_t;

stack_ll_t* stack_ll_create();
stack_ll_status_t stack_ll_push(stack_ll_t* stack, int value);
stack_ll_status_t stack_ll_pop(stack_ll_t* stack, int* value);
stack_ll_status_t stack_ll_peak(stack_ll_t* stack, int* value);
void stack_ll_clear(stack_ll_t stack);
void stack_ll_free(stack_ll_t stack);

size_t stack_ll_get_size(stack_ll_t* stack);
static inline int stack_ll_is_empty(stack_ll_t* stack) {
  return stack_ll_get_size(stack) == 0;
}

#endif // !STACK_LL_H
