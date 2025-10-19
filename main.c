// ============================================================================
// main.c — Test driver for Binary Search Tree (bst.c / bst.h)
// Demonstrates insertion, traversal, search, and deletion operations.
// ============================================================================

#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

static void print_status(bst_status_t status) {
  switch (status) {
  case BST_OK:
    printf("[OK]\n");
    break;
  case BST_ERR_NULL:
    printf("[ERROR] Null tree pointer.\n");
    break;
  case BST_ERR_EMPTY:
    printf("[ERROR] Tree is empty.\n");
    break;
  case BST_ERR_ALLOC:
    printf("[ERROR] Memory allocation failed.\n");
    break;
  case BST_ERR_NOT_FOUND:
    printf("[ERROR] Node not found.\n");
    break;
  default:
    printf("[ERROR] Unknown status code: %d\n", status);
    break;
  }
}

// ----------------------------------------------------------------------------
// Test Scenario
// ----------------------------------------------------------------------------

int main(void) {
  printf("=== Binary Search Tree Test ===\n\n");

  bst_t* tree = bst_create();
  if (!tree) {
    fprintf(stderr, "Failed to create BST.\n");
    return EXIT_FAILURE;
  }

  // ----- Insertion Test -----------------------------------------------------
  int values[] = {8, 3, 10, 1, 6, 14, 4, 7, 13};
  size_t n = sizeof(values) / sizeof(values[0]);

  printf("Inserting values: ");
  for (size_t i = 0; i < n; ++i) {
    printf("%d ", values[i]);
    bst_insert(tree, values[i]);
  }
  putchar('\n');

  printf("\nTree size after insertion: %zu\n", bst_get_size(tree));

  // ----- Traversals ---------------------------------------------------------
  printf("\nInorder traversal   (sorted): ");
  bst_traverse_inorder(tree);

  printf("Preorder traversal  (root-first): ");
  bst_traverse_preorder(tree);

  printf("Postorder traversal (root-last): ");
  bst_traverse_postorder(tree);

  // ----- Search Test --------------------------------------------------------
  int search_keys[] = {6, 13, 9};
  printf("\nSearch results:\n");
  for (size_t i = 0; i < 3; ++i) {
    int key = search_keys[i];
    printf("  Contains %2d?  %s\n", key,
           bst_contains(tree, key) ? "Yes" : "No");
  }

  // ----- Deletion Test ------------------------------------------------------
  printf("\nDeleting nodes: 1, 6, 10, 99 (nonexistent)\n");

  print_status(bst_delete(tree, 1));  // leaf
  print_status(bst_delete(tree, 6));  // node with two children
  print_status(bst_delete(tree, 10)); // node with one child
  print_status(bst_delete(tree, 99)); // non-existent node

  printf("\nTree after deletions (inorder): ");
  bst_traverse_inorder(tree);

  printf("Tree size after deletions: %zu\n", bst_get_size(tree));

  // ----- Clear / Free Test --------------------------------------------------
  printf("\nClearing tree...\n");
  bst_clear(tree);
  printf("Tree cleared. Size = %zu\n", bst_get_size(tree));

  printf("\nReinserting values 5, 2, 8...\n");
  bst_insert(tree, 5);
  bst_insert(tree, 2);
  bst_insert(tree, 8);
  bst_traverse_inorder(tree);

  printf("\nFreeing tree...\n");
  bst_free(tree);

  printf("=== BST Test Completed ===\n");
  return EXIT_SUCCESS;
}
