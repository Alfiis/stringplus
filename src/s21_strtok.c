#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *last = s21_NULL;
  char *begin_part = s21_NULL;
  char *next_part = s21_NULL;
  if (str != s21_NULL) {
    s21_size_t strlen = s21_strlen(str);
    s21_size_t non_delims_num = s21_strspn(str, delim);
    if (non_delims_num != 0) {
      if (non_delims_num == strlen) {
        begin_part = s21_NULL;
      } else {
        begin_part = &str[non_delims_num];
      }
    } else {
      if (non_delims_num == strlen) {
        begin_part = s21_NULL;
      } else {
        begin_part = str;
      }
    }
    if (begin_part != s21_NULL) {
      char *first_entry = s21_strpbrk(begin_part, delim);
      if (first_entry == s21_NULL) {
        last = s21_NULL;
      } else {
        *first_entry = '\0';
        if (*(first_entry + 1) != '\0') {
          last = (first_entry + 1);
        }
      }
    }
  } else {
    if (last == s21_NULL) {
      next_part = s21_NULL;
    } else {
      s21_size_t strlen = s21_strlen(last);
      s21_size_t non_delims_num = s21_strspn(last, delim);
      if (non_delims_num != 0) {
        if (non_delims_num == strlen) {
          next_part = s21_NULL;
        } else {
          next_part = (last + non_delims_num);
        }
      } else {
        next_part = last;
      }
      if (next_part != s21_NULL) {
        char *next_entry = s21_strpbrk(next_part, delim);
        if (next_entry == s21_NULL) {
          last = s21_NULL;
        } else {
          *next_entry = '\0';
          if (*(next_entry + 1) != '\0') {
            last = (next_entry + 1);
          } else {
            last = s21_NULL;
          }
        }
      }
    }
  }
  return str != s21_NULL ? begin_part : next_part;
}

