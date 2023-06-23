#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    char *tmp1;
    char *tmp2;
    unsigned char c1;
    unsigned char c2;
    tmp1 = (char *)str1;
    tmp2 = (char *)str2;
    while (n--) {
        c1 = (unsigned char)*tmp1++;
        c2 = (unsigned char)*tmp2++;
        if (c1 != c2)
            return (c1 - c2);
    }
    return (0);
}
