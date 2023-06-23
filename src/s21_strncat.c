#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
    char *temp = dest;
    while (*dest++) {}
    dest--;

    while (n--) {
        if ((*dest++ = *src++) == '\0')
            return(temp);
    }
    *dest = '\0';
    return(temp);
}
