#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
    s21_size_t i;
    i = 0;
    if (n == 0 || n + 1 < n || n + 1 <= 0)
        return 0;
    while (str1[i] == str2[i] && str1[i] != '\0' && str2[i] != '\0' && i < n-1)
        i++;
    return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}
