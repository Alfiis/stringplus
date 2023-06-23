#include "s21_string.h"

void s21_itoa(int k, char *str) {
    if (k < 0) {
        k = abs(k);
        int i = 0, j = 0;
        j = k;
        for (i = 1; j >= 10; j /= 10)
            i = i * 10;
        *str++ = '-';
        for (; i > 0; i /= 10) {
            *str++ = '0' + k / i;
            k %= i;
        }
        *str = '\0';
    } else {
        int i = 0, j = 0;
        j = k;
        for (i = 1; j >= 10; j /= 10)
            i *= 10;
        for (; i > 0; i /= 10) {
            *str++ = '0' + k / i;
            k %= i;
        }
        *str = '\0';
    }
}
