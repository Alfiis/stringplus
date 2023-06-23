#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
        while (*str != '\0' && *str != (char) c) {
            ++str;
        }
        if (*str == (char) c) {
            return (char *) str;
        }
        return NULL;
}
