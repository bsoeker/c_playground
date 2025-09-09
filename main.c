#include "stack.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    Stack *s = stack_create(10);
    for (int i = 0; i < 10; i++)
        stack_push(s, (i + 1) * 10);

    while (!isEmpty(s))
        printf("%d\n", stack_pop(s));

    return 0;
}
