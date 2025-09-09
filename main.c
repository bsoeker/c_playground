#include <stdio.h>

void say_Hello(char *str) { printf("Hello %s\n", str); }

int main(int argc, char *argv[]) {
    char *str = "ChatGPT";
    say_Hello(str);

    printf("Do some other stuff in main");

    return 0;
}
