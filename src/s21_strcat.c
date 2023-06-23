#include "s21_string.h"

char *s21_strcat(char *dest, const char *src) {
    char *temp = dest;
    while (*temp) {
        temp++;
    }
    while ((*temp++ = *src++) != '\0') {
    }
    return dest;
}
