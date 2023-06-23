#include "s21_string.h"

char * s21_strstr(const char * haystack, const char * needle) {
s21_size_t res;
s21_size_t cnt;

res = 0;
if (s21_strcmp("", needle) == 0)
return ((char *)haystack);
while (haystack[res] != '\0') {
    cnt = 0;
    while (needle[cnt] == haystack[res + cnt] && haystack[res + cnt] != '\0')
    cnt++;
    if (needle[cnt] == '\0')
    return ((char *)&haystack[res]);
    res++;
    }
    return (s21_NULL);
}
