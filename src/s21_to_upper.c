#include "s21_string.h"

void *s21_to_upper(const char *str) {
    static char *buf;
    buf = malloc(s21_strlen(str) +1);
    void *pr = s21_NULL;
    s21_size_t wd = s21_strlen(str) + 1;
    for (s21_size_t i = 0; i < wd; i++) {
        if (str[i] >= 'a' && str[i] <= 'z')
            buf[i] = str[i] - 32;
        else
            buf[i] = str[i];
        }
    buf[wd] = '\0';
    pr = (void *)buf;
    return pr;
}
