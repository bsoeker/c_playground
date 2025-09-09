#include "my_strlib.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    char buffer[1024];
    printf("%s\n", my_strcpy(buffer, "Hello"));

    char *s = my_strcat(buffer, ", World!\n");

    printf("%d\n", my_strcmp(buffer, s));

    return 0;
}
