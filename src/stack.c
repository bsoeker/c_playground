#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Stack *stack_create(size_t cap) {
    Stack *s = malloc(sizeof *s);
    s->data = malloc(cap * sizeof(int));
    s->size = 0;
    s->cap = cap;
    return s;
}

static int resize(Stack *s, size_t newCap) {
    int *tmp = realloc(s->data, newCap * sizeof(int));
    if (!tmp) {
        printf("realloc() failed!");
        return 0;
    }

    s->data = tmp;
    s->cap = newCap;
    return 1;
}

void stack_push(Stack *s, int value) {
    if (s->size == s->cap)
        if (!resize(s, s->cap * 2))
            return;

    s->data[s->size++] = value;
}

int stack_pop(Stack *s) {
    if (s->size == 0) {
        fprintf(stderr, "Stack underflow!");
        exit(EXIT_FAILURE);
    }

    return s->data[--s->size];
}

void stack_free(Stack *s) {
    free(s->data);
    free(s);
}
