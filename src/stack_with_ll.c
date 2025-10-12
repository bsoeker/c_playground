#include "stack_with_ll.h"
#include "doubly_linked_list.h"
#include <stdlib.h>

struct stack_ll {
  doubly_linked_list_t* list;
};

stack_ll_t* stack_ll_create() {
  stack_ll_t* stack = malloc(sizeof(*stack));
  if (!stack)
    return NULL;
  stack->list = d_ll_create();

  return stack;
}

stack_ll_status_t stack_ll_push(stack_ll_t* stack, int value) {
  d_ll_push_tail(stack->list, value);

  return STACK_LL_OK;
}
stack_ll_status_t stack_ll_pop(stack_ll_t* stack, int* value) {
  d_ll_pop_tail(stack->list, value);

  return STACK_LL_OK;
}
stack_ll_status_t stack_ll_peak(stack_ll_t* stack, int* value) {
  d_ll_peek_tail(stack->list, value);

  return STACK_LL_OK;
}
void stack_ll_clear(stack_ll_t stack) { d_ll_clear(stack.list); }
void stack_ll_free(stack_ll_t stack) { d_ll_free(stack.list); }

size_t stack_ll_get_size(stack_ll_t* stack) {
  return d_ll_get_size(stack->list);
}
