#include <stdarg.h>
#include <unistd.h> // for write()

static void print_char(char c) { write(1, &c, 1); }

static void print_string(const char* s) {
  while (*s) {
    print_char(*s++);
  }
}

static void print_number(int num, int base) {
  char digits[] = "0123456789abcdef";
  char buf[32]; // to match int size
  int i = 0;

  if (num == 0) {
    print_char('0');
    return;
  }

  if (num < 0 && base == 10) {
    print_char('-');
    num = -num;
  }

  while (num > 0) {
    buf[i++] = digits[num % base];
    num /= base;
  }

  while (i--) {
    print_char(buf[i]);
  }
}

void my_printf(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);

  for (const char* p = fmt; *p; p++) {
    if (*p == '%') {
      p++;
      if (*p == 'd') {
        int val = va_arg(args, int);
        print_number(val, 10);
      } else if (*p == 'x') {
        int val = va_arg(args, int);
        print_number(val, 16);
      } else if (*p == 's') {
        char* s = va_arg(args, char*);
        print_string(s);
      }
    } else {
      print_char(*p);
    }
  }

  va_end(args);
}
