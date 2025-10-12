#include "queue_with_ll.h"
#include "stack_with_ll.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  stack_ll_t* stack = stack_ll_create();

  for (int i = 0; i < 10; i++) {
    stack_ll_push(stack, i);
  }

  int* value = malloc(sizeof(int));
  while (!stack_ll_is_empty(stack)) {
    stack_ll_pop(stack, value);
    printf("%d\n", *value);
  }

  queue_ll_t* queue = queue_ll_create();

  for (int i = 0; i < 10; i++) {
    queue_ll_push(queue, i);
  }

  while (!queue_ll_is_empty(queue)) {
    queue_ll_pop(queue, value);
    printf("%d\n", *value);
  }

  return 0;
}
