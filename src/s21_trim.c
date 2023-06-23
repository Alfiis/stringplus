#include "s21_string.h"

int start(const char *mani, const char *minor, s21_size_t head,
            s21_size_t nohead) {
    int start_i = 0;
    for (s21_size_t i = 0; i < head; i++) {
      int flag1 = 0;
      for (s21_size_t j = 0; j < nohead; j++) {
        if (mani[i] == minor[j]) {
          flag1 = 1;
          break;
        }
      }
      if (flag1 == 1) {
        start_i++;
      } else {
        break;
      }
    }
    return start_i;
}

int end(const char *mani, const char *minor, s21_size_t head,
        s21_size_t nohead) {
    int end_i = head;
    for (int i = head - 1; i > -1; i--) {
      int flag2 = 0;
      for (s21_size_t j = 0; j < nohead; j++) {
        if (mani[i] == minor[j]) {
          flag2 = 1;
          break;
        }
      }
      if (flag2 == 1) {
        end_i--;
      } else {
        break;
      }
    }
    return end_i;
}

void *s21_trim(const char *src, const char *trim_chars) {
    char *mani = (char *)src;
    char *minor = (char *)trim_chars;
    char *arr;
    int man = 1;
    if (minor == s21_NULL) {
      trim_chars = " ";
      minor = (char *)trim_chars;
    }
    if (mani == s21_NULL) man = 0;
    if (man) {
      int arr_i = 0;
      s21_size_t head = s21_strlen(src);
      s21_size_t nohead = s21_strlen(trim_chars);
      arr = (char *)malloc((head + 1) * sizeof(char));
      int st_i = start(mani, minor, head, nohead);
      int en_i = end(mani, minor, head, nohead);
      for (int i = st_i; i < en_i; i++) {
        arr[arr_i] = src[i];
        arr_i++;
      }
      arr[arr_i] = '\0';
    }
    if (man == 0) {
      return s21_NULL;
    } else {
      return (char *)arr;
  }
}
