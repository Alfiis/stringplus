#include "s21_string.h"

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
    if (n == 0 || dest == src || n + 1 <= 0 || n + 1 < n)
    return (dest);
    if (src <= dest)
    while (n--)
    ((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
    else
    s21_memcpy(dest, src, n);
    return ((void *)dest);
}
