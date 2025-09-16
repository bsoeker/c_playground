#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

stack_t *stack_create(size_t cap) {
    stack_t *s = malloc(sizeof *s);
    if (!s)
        return NULL;
    s->data = malloc(cap * sizeof(int));
    if (!s->data) {
        free(s);
        return NULL;
    }
    s->size = 0;
    s->cap = cap;
    return s;
}

static int resize(stack_t *s, size_t new_cap) {
    int *tmp = realloc(s->data, new_cap * sizeof(int));
    if (!tmp) {
        printf("realloc() failed!");
        return 0;
    }

    s->data = tmp;
    s->cap = new_cap;
    return 1;
}

void stack_push(stack_t *s, int value) {
    if (s->size == s->cap)
        if (!resize(s, s->cap * 2))
            return;

    s->data[s->size++] = value;
}

int stack_pop(stack_t *s) {
    if (s->size == 0) {
        fprintf(stderr, "Stack underflow!\n");
        exit(EXIT_FAILURE);
    }

    return s->data[--s->size];
}

void stack_free(stack_t *s) {
    free(s->data);
    free(s);
}
