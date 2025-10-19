// ============================================================================
// bst.c — Binary Search Tree implementation
// Provides insertion, deletion, traversal, and lookup operations.
// ============================================================================

#include "bst.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// ============================================================================
// Error & Guard Macros
// ============================================================================

// ----- Pointer Checks -------------------------------------------------------

#define BST_CHECK_PTR_RET(bst, retval)                                         \
  do {                                                                         \
    if (!(bst)) {                                                              \
      fprintf(stderr, "BST error: %s called with NULL\n", __func__);           \
      return retval;                                                           \
    }                                                                          \
  } while (0)

#define BST_CHECK_PTR(bst)                                                     \
  do {                                                                         \
    if (!(bst)) {                                                              \
      fprintf(stderr, "BST error: %s called with NULL\n", __func__);           \
      return;                                                                  \
    }                                                                          \
  } while (0)

// ----- Memory Allocation Checks ---------------------------------------------

#define BST_CHECK_NODE_ALLOC(node)                                             \
  do {                                                                         \
    if (!(node)) {                                                             \
      fprintf(stderr, "BST error: malloc() call on node creation failed!\n");  \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
  } while (0)

#define BST_CHECK_TREE_ALLOC(tree)                                             \
  do {                                                                         \
    if (!(tree)) {                                                             \
      fprintf(stderr, "BST error: malloc() call on tree creation failed!\n");  \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
  } while (0)

// ----- Empty Tree Guards ----------------------------------------------------

#define BST_EXIT_IF_EMPTY(bst, retval)                                         \
  do {                                                                         \
    if (bst_is_empty(bst)) {                                                   \
      fprintf(stderr, "Tree is empty!\n");                                     \
      return retval;                                                           \
    }                                                                          \
  } while (0)

#define BST_ABORT_IF_EMPTY(bst)                                                \
  do {                                                                         \
    if (bst_is_empty(bst)) {                                                   \
      fprintf(stderr, "Tree is empty!\n");                                     \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
  } while (0)

// ============================================================================
// Internal Data Structures
// ============================================================================

typedef struct node {
  int value;
  struct node* left_child;
  struct node* right_child;
} node_t;

struct bst {
  node_t* root;
  size_t size;
};

// ============================================================================
// Internal Helper Functions
// ============================================================================

static node_t* create_node(int value) {
  node_t* node = malloc(sizeof(*node));
  BST_CHECK_NODE_ALLOC(node);

  node->value = value;
  node->left_child = NULL;
  node->right_child = NULL;

  return node;
}

static node_t* insert_node(node_t* root, int value, int* inserted) {
  if (root == NULL) {
    *inserted = 1;
    return create_node(value);
  }

  if (value < root->value)
    root->left_child = insert_node(root->left_child, value, inserted);
  else if (value > root->value)
    root->right_child = insert_node(root->right_child, value, inserted);

  return root;
}

static const node_t* search(const node_t* root, int value) {
  if (!root)
    return NULL;
  if (value == root->value)
    return root;

  return value < root->value ? search(root->left_child, value)
                             : search(root->right_child, value);
}

static const node_t* find_min(const node_t* node) {
  while (node && node->left_child)
    node = node->left_child;
  return node;
}

static node_t* delete_node(node_t* root, int value, int* deleted) {
  if (!root)
    return NULL;

  if (value < root->value)
    root->left_child = delete_node(root->left_child, value, deleted);
  else if (value > root->value)
    root->right_child = delete_node(root->right_child, value, deleted);
  else {
    // Node found
    if (!root->left_child) {
      node_t* temp = root->right_child;
      free(root);
      *deleted = 1;
      return temp;
    } else if (!root->right_child) {
      node_t* temp = root->left_child;
      free(root);
      *deleted = 1;
      return temp;
    }

    // For a generic tree, we’d need to rearrange child pointers.
    // For a BST, copying the successor’s value is sufficient.
    const node_t* succ = find_min(root->right_child);
    root->value = succ->value;
    root->right_child = delete_node(root->right_child, succ->value, deleted);
  }

  return root;
}

// ============================================================================
// Tree Traversals
// ============================================================================

static void preorder(const node_t* root) {
  if (!root)
    return;

  printf("%d ", root->value);
  preorder(root->left_child);
  preorder(root->right_child);
}

static void inorder(const node_t* root) {
  if (!root)
    return;

  inorder(root->left_child);
  printf("%d ", root->value);
  inorder(root->right_child);
}

static void postorder(const node_t* root) {
  if (!root)
    return;

  postorder(root->left_child);
  postorder(root->right_child);
  printf("%d ", root->value);
}

static void free_nodes(node_t* root) {
  if (!root)
    return;

  free_nodes(root->left_child);
  free_nodes(root->right_child);
  free(root);
}

// ============================================================================
// Public API
// ============================================================================

bst_t* bst_create(void) {
  bst_t* tree = malloc(sizeof(*tree));
  BST_CHECK_TREE_ALLOC(tree);

  tree->root = NULL;
  tree->size = 0;

  return tree;
}

bst_status_t bst_insert(bst_t* tree, int value) {
  BST_CHECK_PTR_RET(tree, BST_ERR_NULL);

  int inserted = 0;
  tree->root = insert_node(tree->root, value, &inserted);
  tree->size += inserted;

  return BST_OK;
}

bst_status_t bst_delete(bst_t* tree, int value) {
  BST_CHECK_PTR_RET(tree, BST_ERR_NULL);
  BST_EXIT_IF_EMPTY(tree, BST_ERR_EMPTY);

  int deleted = 0;
  tree->root = delete_node(tree->root, value, &deleted);
  tree->size -= deleted;

  return deleted ? BST_OK : BST_ERR_NOT_FOUND;
}

void bst_traverse_preorder(const bst_t* tree) {
  preorder(tree->root);
  putchar('\n');
}

void bst_traverse_inorder(const bst_t* tree) {
  inorder(tree->root);
  putchar('\n');
}

void bst_traverse_postorder(const bst_t* tree) {
  postorder(tree->root);
  putchar('\n');
}

int bst_contains(const bst_t* tree, int value) {
  BST_ABORT_IF_EMPTY(tree);
  return search(tree->root, value) ? 1 : 0;
}

void bst_clear(bst_t* tree) {
  BST_CHECK_PTR(tree);

  free_nodes(tree->root);
  tree->root = NULL;
  tree->size = 0;
}

void bst_free(bst_t* tree) {
  BST_CHECK_PTR(tree);

  free_nodes(tree->root);
  free(tree);
}

size_t bst_get_size(const bst_t* tree) { return tree->size; }
