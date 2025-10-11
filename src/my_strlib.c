#include "my_strlib.h"
#include <stddef.h>

size_t my_strlen(const char* p) {
  size_t len = 0;

  while (*p != '\0') {
    len++;
    p++;
  }

  return len;
}

char* my_strcpy(char* dest, const char* src) {
  char* ret = dest;
  while ((*dest++ = *src++) != '\0')
    ;
  return ret;
}

char* my_strcat(char* dest, const char* src) {
  size_t len = my_strlen(dest);
  my_strcpy(dest + len, src);

  return dest;
}

int my_strcmp(const char* s1, const char* s2) {
  while (*s1 && (*s1 == *s2)) {
    s1++;
    s2++;
  }

  return (unsigned char)*s1 - (unsigned char)*s2;
}
