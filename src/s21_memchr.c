#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
    s21_size_t i;
    unsigned char *arrCha;

    if (n + 1 <= 0 || n == 0 || n + 1 < n)
        return (s21_NULL);
    i = 0;
    arrCha = (unsigned char *)str;
    while (n--) {
        if (arrCha[i] == (unsigned char)c)
            return ((void *)str + i);
        i++;
    }
    return (s21_NULL);
}

