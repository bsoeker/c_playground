#ifndef BST_H
#define BST_H

#include <stddef.h>

typedef struct bst bst_t;

typedef enum {
  BST_OK = 0,            // success
  BST_ERR_NULL = -1,     // NULL pointer passed
  BST_ERR_EMPTY = -2,    // tree empty
  BST_ERR_ALLOC = -3,    // malloc() failed
  BST_ERR_NOT_FOUND = -4 // node not found during deletion
} bst_status_t;

bst_t* bst_create();
bst_status_t bst_insert(bst_t* tree, int value);
bst_status_t bst_delete(bst_t* tree, int value);
void bst_traverse_preorder(const bst_t* tree);
void bst_traverse_inorder(const bst_t* tree);
void bst_traverse_postorder(const bst_t* tree);
int bst_contains(const bst_t* tree, int value);
void bst_clear(bst_t* tree);
void bst_free(bst_t* tree);

size_t bst_get_size(const bst_t* tree);
static inline int bst_is_empty(const bst_t* tree) {
  return bst_get_size(tree) == 0;
}

#endif // !BST_H
