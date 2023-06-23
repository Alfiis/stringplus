#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
    unsigned char *array1;
    unsigned char *array2;
    if (n == 0 || n + 1 <= 0 || n + 1 < n)
        return (dest);
    array1 = (unsigned char *)dest;
    array2 = (unsigned char *)src;
    while (n != 0) {
        *array1++ = *array2++;
        n--;
    }
    return ((void *)dest);
}
