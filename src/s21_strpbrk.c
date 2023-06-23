#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
    int i = 0, j;
    while (str1[i] != '\0') {
        j = 0;
        while (str2[j] != '\0') {
            if (str1[i] == str2[j]) {
                return ((char *)str1+i);
            }
            j++;
        }
        i++;
    }
    return s21_NULL;
}
