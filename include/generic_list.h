#pragma once
#include <stdlib.h>

#define DEFINE_LIST_TYPE(T, Name)                                              \
    typedef struct Name##_node {                                               \
        T value;                                                               \
        struct Name##_node *next;                                              \
    } Name##_node;                                                             \
                                                                               \
    typedef struct {                                                           \
        Name##_node *head;                                                     \
        Name##_node *tail;                                                     \
        size_t size;                                                           \
    } Name##_list;                                                             \
                                                                               \
    static inline void Name##_init(Name##_list *ll) {                          \
        ll->head = ll->tail = NULL;                                            \
        ll->size = 0;                                                          \
    }                                                                          \
                                                                               \
    static inline void Name##_append(Name##_list *ll, T val) {                 \
        Name##_node *n = malloc(sizeof(*n));                                   \
        if (!n)                                                                \
            return; /* out of mem, noop */                                     \
        n->value = val;                                                        \
        n->next = NULL;                                                        \
        if (ll->tail)                                                          \
            ll->tail->next = n;                                                \
        else                                                                   \
            ll->head = n;                                                      \
        ll->tail = n;                                                          \
        ll->size++;                                                            \
    }                                                                          \
                                                                               \
    static inline int Name##_pop_front(Name##_list *ll, T *out) {              \
        if (!ll->head)                                                         \
            return 0;                                                          \
        Name##_node *old = ll->head;                                           \
        *out = old->value;                                                     \
        ll->head = old->next;                                                  \
        if (!ll->head)                                                         \
            ll->tail = NULL;                                                   \
        free(old);                                                             \
        ll->size--;                                                            \
        return 1;                                                              \
    }                                                                          \
                                                                               \
    static inline void Name##_clear(Name##_list *ll) {                         \
        Name##_node *cur = ll->head;                                           \
        while (cur) {                                                          \
            Name##_node *next = cur->next;                                     \
            free(cur);                                                         \
            cur = next;                                                        \
        }                                                                      \
        ll->head = ll->tail = NULL;                                            \
        ll->size = 0;                                                          \
    }
