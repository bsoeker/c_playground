#ifndef STACK_H
#define STACK_H

#include <stddef.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
    size_t cap;

} Stack;

Stack *stack_create(size_t cap);
void stack_push(Stack *s, int value);
int stack_pop(Stack *s);
void stack_free(Stack *s);
static inline int getSize(Stack *s) { return s->size; };
static inline int isEmpty(Stack *s) { return s->size == 0; }

#endif // STACK_H
