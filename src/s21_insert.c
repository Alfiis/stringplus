#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
    void *pr = s21_NULL;
    int ep = s21_strlen(src) + s21_strlen(str);
    if (s21_strlen(src) >= start_index) {
        static char *buf;
        int fg = 0;
        buf = malloc(ep);
        for (s21_size_t i = 0; i < start_index; i++) {
            buf[i] = src[i];
            fg++;
        }
        for (s21_size_t i = start_index; i < ep + start_index; i++) {
            buf[i] = str[i - start_index];
        }
        for (s21_size_t i = s21_strlen(str) + fg; i < ep + start_index; i++) {
            buf[i] = src[i - s21_strlen(str)];
        }
        buf[ep] = '\0';
        pr = (void*)buf;
    }
    return pr;
}
