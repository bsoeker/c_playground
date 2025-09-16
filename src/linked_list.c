#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

#define LL_CHECK_PTR(ll)                                                       \
    do {                                                                       \
        if (!(ll)) {                                                           \
            fprintf(stderr, "Linked list error: %s called with NULL\n",        \
                    __func__);                                                 \
            return;                                                            \
        }                                                                      \
    } while (0)

#define LL_CHECK_PTR_RET(ll, retval)                                           \
    do {                                                                       \
        if (!(ll)) {                                                           \
            fprintf(stderr, "Linked list error: %s called with NULL\n",        \
                    __func__);                                                 \
            return (retval);                                                   \
        }                                                                      \
    } while (0)

typedef struct node {
    int value;
    struct node *next;
} node_t;

struct linked_list {
    node_t *head;
    node_t *tail;
    size_t size;
};

linked_list_t *ll_create() {
    linked_list_t *ll = malloc(sizeof(*ll));
    if (!ll)
        return NULL;

    ll->head = ll->tail = NULL;
    ll->size = 0;
    return ll;
}

ll_status_t ll_append(linked_list_t *ll, int value) {
    LL_CHECK_PTR_RET(ll, LL_ERR_NULL);

    node_t *new_node = malloc(sizeof(*new_node));
    if (!new_node)
        return LL_ERR_ALLOC;

    new_node->value = value;
    new_node->next = NULL;

    if (ll->tail) {
        ll->tail->next = new_node;
        ll->tail = new_node;
    } else {
        ll->head = ll->tail = new_node;
    }

    ll->size++;
    return LL_OK;
}

ll_status_t ll_pop_head(linked_list_t *ll, int *value) {
    LL_CHECK_PTR_RET(ll, LL_ERR_NULL);

    if (ll_is_empty(ll))
        return LL_ERR_EMPTY;

    node_t *old_head = ll->head;
    *value = old_head->value;

    ll->head = old_head->next;
    free(old_head);

    if (!ll->head)
        ll->tail = NULL;

    ll->size--;
    return LL_OK;
}

ll_status_t ll_peek_head(linked_list_t *ll, int *value) {
    LL_CHECK_PTR_RET(ll, LL_ERR_NULL);

    if (ll_is_empty(ll))
        return LL_ERR_EMPTY;

    *value = ll->head->value;
    return LL_OK;
}

ll_status_t ll_peek_tail(linked_list_t *ll, int *value) {
    LL_CHECK_PTR_RET(ll, LL_ERR_NULL);

    if (ll_is_empty(ll))
        return LL_ERR_EMPTY;

    *value = ll->tail->value;
    return LL_OK;
}

void ll_clear(linked_list_t *ll) {
    node_t *cur = ll->head;

    while (cur) {
        node_t *next = cur->next;
        free(cur);
        cur = next;
    }

    ll->head = ll->tail = NULL;
    ll->size = 0;
}

void ll_free(linked_list_t *ll) {
    ll_clear(ll);
    free(ll);
}

size_t ll_get_size(const linked_list_t *ll) { return ll ? ll->size : 0; }
