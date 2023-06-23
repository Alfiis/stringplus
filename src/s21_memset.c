#include "s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
    char ch = (char)c;
    char * str1 = (char*)str;
    while (n--) {
        *str1++ = ch;
    }
    return str;
}
