#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

vector_t *vector_create(size_t cap, size_t elem_size) {
    vector_t *v = malloc(sizeof *v);
    if (!v)
        return NULL;
    v->data = malloc(cap * sizeof(elem_size));
    if (!v->data) {
        free(v);
        return NULL;
    }
    v->size = 0;
    v->cap = cap;
    v->elem_size = elem_size;
    return v;
}

static int vector_resize(vector_t *v, size_t new_cap) {
    int *tmp = realloc(v->data, new_cap * sizeof(v->elem_size));
    if (!tmp) {
        printf("realloc() failed!");
        return 0;
    }

    v->data = tmp;
    v->cap = new_cap;
    return 1;
}

void vector_push_back(vector_t *v, const void *value) {
    if (v->size == v->cap)
        if (!vector_resize(v, v->cap * 2))
            return;

    void *dest = (char *)v->data + v->size * v->elem_size;
    memcpy(dest, value, v->elem_size);
    v->size++;
}

void *vector_pop_back(vector_t *v) {
    if (vector_is_empty(v)) {
        fprintf(stderr, "Vector underflow!\n");
        exit(EXIT_FAILURE);
    }

    v->size--;
    return (char *)v->data + v->size * v->elem_size;
}

void *vector_at(vector_t *v, size_t index) {
    if (vector_is_empty(v)) {
        printf("Vector is empty!\n");
        exit(EXIT_FAILURE);
    }
    if (index >= v->size) {
        fprintf(stderr, "Index out of bounds!");
        exit(EXIT_FAILURE);
    }

    return (char *)v->data + index * v->elem_size;
}

void vector_free(vector_t *v) {
    free(v->data);
    free(v);
}
