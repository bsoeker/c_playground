#include "doubly_linked_list.h"
#include <stdio.h>
#include <stdlib.h>

static void print_state(const doubly_linked_list_t* list) {
  if (!list) {
    printf("[!] List pointer is NULL\n");
    return;
  }

  int head_val = 0, tail_val = 0;
  size_t size = d_ll_get_size((doubly_linked_list_t*)list);

  if (d_ll_peek_head((doubly_linked_list_t*)list, &head_val) == D_LL_OK
      && d_ll_peek_tail((doubly_linked_list_t*)list, &tail_val) == D_LL_OK) {
    printf("List size: %zu | head: %d | tail: %d\n", size, head_val, tail_val);
  } else {
    printf("List size: %zu | (empty)\n", size);
  }
}

int main(void) {
  doubly_linked_list_t* list = d_ll_create();
  if (!list) {
    fprintf(stderr, "Failed to create list.\n");
    return EXIT_FAILURE;
  }

  printf("\n=== INITIAL STATE ===\n");
  print_state(list);

  printf("\n=== PUSH HEAD (0..2) ===\n");
  for (int i = 0; i < 3; i++) {
    d_ll_push_head(list, i);
    print_state(list);
  }

  printf("\n=== PUSH TAIL (10..12) ===\n");
  for (int i = 10; i < 13; i++) {
    d_ll_push_tail(list, i);
    print_state(list);
  }

  printf("\n=== POP HEAD twice ===\n");
  for (int i = 0; i < 2; i++) {
    int val;
    if (d_ll_pop_head(list, &val) == D_LL_OK)
      printf("Popped head: %d\n", val);
    print_state(list);
  }

  printf("\n=== POP TAIL twice ===\n");
  for (int i = 0; i < 2; i++) {
    int val;
    if (d_ll_pop_tail(list, &val) == D_LL_OK)
      printf("Popped tail: %d\n", val);
    print_state(list);
  }

  printf("\n=== FINAL CLEANUP ===\n");
  print_state(list);

  d_ll_clear(list);
  print_state(list);

  return 0;
}
