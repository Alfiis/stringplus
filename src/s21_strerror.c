#include "s21_string.h"

char *s21_strerror(int errnum) {
    static char *str[] = s21_error_array;
    int max;
    char error[4096] = {'\0'};
    char stt[10];
    static char strr[4096] = {'\0'};
    for (int i = 0; i < 4096; i++) strr[i] = '\0';

#if defined(__APPLE__) && defined(__MACH__)
    max = 106;
#else
    max = 133;
#endif

    if (errnum > max || errnum < 0) {
        s21_itoa(errnum, stt);
        s21_strcpy(error, "Unknown error: ");
        s21_strncat(error, stt, s21_strlen(error));
    } else {
        s21_strcat(error, str[errnum]);
    }
    s21_strcat(strr, error);
    return strr;
}
