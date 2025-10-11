#ifndef MY_STRLIB_H
#define MY_STRLIB_H

#include <stddef.h>

size_t my_strlen(const char* p);
char* my_strcpy(char* dest, const char* src);
char* my_strcat(char* dest, const char* src);
int my_strcmp(const char* s1, const char* s2);

#endif // !MY_STRLIB_H
