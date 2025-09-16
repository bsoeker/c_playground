#include "generic_list.h"
#include <stdio.h>
#include <stdlib.h>

DEFINE_LIST_TYPE(int, int)

int main(int argc, char *argv[]) {
    int_list *l = malloc(sizeof(*l));
    int_init(l);
    int_append(l, 10);

    int *p = malloc(4);

    int_pop_front(l, p);

    printf("%d\n", *p);

    return 0;
}
