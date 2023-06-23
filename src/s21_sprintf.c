#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  va_list argList;
  va_start(argList, format);
  s21_size_t i = 0, banner = 0, mistake = 0;
  char *string_start = str;
  str = s21_strcpy(str, "");
  while (*format && mistake == 0) {
    FORMAT FFormat = {};
    FFormat.width = FFormat.tolerance = -1;
    FFormat.flag_mistake = FFormat.flag_sharp = FFormat.flag_zero =
        FFormat.flag_minus = FFormat.flag_space = FFormat.flag_plus = 0;
    if (*format == '%') {
      banner = 1;
      format++;
    } else {
      str[i++] = *(format++);
      str[i] = '\0';
    }

    if (banner == 1 && is_flag(*format))
      while (is_flag(*format)) s21_set_flag(&FFormat, format++);

    if (banner == 1 && (is_digit(*format) || *format == '*'))
      format = s21_str_to_int(format, &FFormat.width, &argList);

    if (banner == 1 && *format == '.') {
      FFormat.tolerance = 0;
      format = s21_str_to_int(++format, &FFormat.tolerance, &argList);
    }

    if (banner == 1 && is_len(*format)) FFormat.len = *(format++);

    if (banner == 1 && is_spec(*format)) FFormat.spec = *(format++);

    if (banner == 1) {
      str = s21_format_param_to_str(str, &i, &FFormat, &argList);
      mistake = FFormat.flag_mistake;
    }
    banner = 0;
  }
  va_end(argList);
  if (mistake != 0) *string_start = '\0';
  return mistake == 0 ? (int)s21_strlen(str) : -1;
}

char *s21_format_param_to_str(char *str, s21_size_t *string_len,
                              FORMAT *FFormat, va_list *argList) {
  char *tmp_str = s21_NULL;
  tmp_str = calloc(1000 + FFormat->width + 2, sizeof(char));
  if (tmp_str != s21_NULL) {
    switch (FFormat->spec) {
      case 'd':
      case 'i':
        s21_str_from_d(tmp_str, argList, FFormat);
        break;
      case 'o':
        s21_str_from_o(tmp_str, argList, FFormat);
        break;
      case 'u':
        s21_str_from_u(tmp_str, argList, FFormat);
        break;
      case 'x':
      case 'X':
        s21_str_from_xX(tmp_str, argList, FFormat);
        break;
      case 'e':
      case 'E':
        s21_str_from_eE(tmp_str, argList, FFormat);
        break;
      case 'f':
        s21_str_from_f(tmp_str, argList, FFormat);
        break;
      case 'g':
      case 'G':
        s21_str_from_gG(tmp_str, argList, FFormat);
        break;
      case 'c':
        s21_str_from_c(tmp_str, argList, FFormat);
        break;
      case 's':
        s21_str_from_s(tmp_str, argList, FFormat);
        break;
      case 'p':
        s21_str_from_p(tmp_str, argList, FFormat);
        break;
      case 'n':
        s21_str_from_n(string_len, argList);
        break;
      case '%':
        s21_str_from_perc(tmp_str, FFormat);
        break;
    }
    s21_strcat(str, tmp_str);
    free(tmp_str);
    *string_len = s21_strlen(str);
  }
  return str;
}

char *s21_str_from_f(char *str, va_list *argList, FORMAT *FFormat) {
  long double ld_size;
  double d_size;
  double f_size;

  switch (FFormat->len) {
    case 'l':
      d_size = (double)va_arg(*argList, double);
      s21_lf_to_str(str, d_size, FFormat);
      break;
    case 'L':
      ld_size = va_arg(*argList, long double);
      s21_lf_to_str(str, ld_size, FFormat);
      break;
    default:
      d_size = va_arg(*argList, double);
      f_size = d_size;
      s21_lf_to_str(str, f_size, FFormat);
  }
  s21_sign_flag(str, FFormat);
  s21_lf_width_flag(str, FFormat);
  return str;
}

void s21_set_flag(FORMAT *FFormat, const char *format) {
  switch (*format) {
    case '-':
      FFormat->flag_minus = 1;
      break;
    case '+':
      FFormat->flag_plus = 1;
      break;
    case ' ':
      FFormat->flag_space = 1;
      break;
    case '#':
      FFormat->flag_sharp = 1;
      break;
    case '0':
      FFormat->flag_zero = 1;
      break;
  }
}

void s21_str_from_n(s21_size_t const *string_len, va_list *argList) {
  int *p = va_arg(*argList, int *);
  *p = (int)*string_len;
}

char *s21_str_from_p(char *str, va_list *argList, FORMAT *FFormat) {
  int width = FFormat->width < 15 ? 15 : FFormat->width;
  char *string_start = s21_NULL;
  string_start = str;
  int *p = va_arg(*argList, int *);
  char buf[4] = "x0";
  if (p == s21_NULL) {
    s21_strcpy(buf, "0x0");
  }

  for (int *j = p, k = 0; j && k < width;
       j = (void *)(((s21_size_t)j) >> 4), k++) {
    unsigned int dig = ((s21_size_t)j) % 0x10;
    if (dig < 10 && FFormat->spec == 'p')
      *(string_start++) = (char)('0' + dig);
    else
      *(string_start++) = (char)('a' + (dig - 10));
  }
  *string_start = '\0';
  s21_strcat(str, buf);
  s21_reverse_str(str);
  s21_ll_width_flag(str, FFormat);
  return str;
}

char *s21_str_from_perc(char *str, FORMAT *FFormat) {
  FFormat->tolerance = 0;
  s21_strcat(str, "%");
  s21_ll_tolerance(str, FFormat);
  s21_ll_width_flag(str, FFormat);
  return str;
}

char *s21_str_from_gG(char *str, va_list *argList, FORMAT *FFormat) {
  long double ld_size;
  double d_size;
  double f_size;

  switch (FFormat->len) {
    case 'l':
      d_size = (double)va_arg(*argList, double);
      s21_lgG_to_str(str, d_size, FFormat);
      break;
    case 'L':
      ld_size = va_arg(*argList, long double);
      s21_lgG_to_str(str, ld_size, FFormat);
      break;
    default:
      d_size = va_arg(*argList, double);
      f_size = d_size;
      s21_lgG_to_str(str, f_size, FFormat);
  }
  s21_sign_flag(str, FFormat);
  s21_lf_width_flag(str, FFormat);
  return str;
}

char *s21_str_from_eE(char *str, va_list *argList, FORMAT *FFormat) {
  long double ld_size;
  double d_size;
  double f_size;

  switch (FFormat->len) {
    case 'l':
      d_size = (double)va_arg(*argList, double);
      s21_leE_to_str(str, d_size, FFormat);
      break;
    case 'L':
      ld_size = va_arg(*argList, long double);
      s21_leE_to_str(str, ld_size, FFormat);
      break;
    default:
      d_size = va_arg(*argList, double);
      f_size = d_size;
      s21_leE_to_str(str, f_size, FFormat);
  }
  s21_sign_flag(str, FFormat);
  s21_lf_width_flag(str, FFormat);
  return str;
}

char *s21_leE_to_str(char *str, long double size, FORMAT *FFormat) {
  if (FFormat->tolerance < 0) FFormat->tolerance = 6;
  long double accuracy = 0.0, bogomol;
  int check_work = 0;

  bogomol = modfl(fabsl(size), &accuracy);
  if (fpclassify(size) > 3) {
    while (accuracy >= 10) {
      check_work++;
      modfl(accuracy / 10, &accuracy);
    }
    if (check_work == 0 && accuracy < 1) {
      while (truncl(bogomol * powl(10, check_work * -1)) < 1) {
        check_work--;
      }
    }
  }

  if (fpclassify(size) > 2) {
    size = size / powl(10, check_work);
    s21_sprintf(str, FFormat->flag_sharp == 1 ? "%#.*Lfe%+.2d" : "%.*Lfe%+.2d",
                FFormat->tolerance, size, check_work);
  } else {
    s21_sprintf(str, "%.*Lf", FFormat->tolerance);
    FFormat->flag_zero = 0;
  }
  if (FFormat->spec == 'E') {
    char *p = s21_NULL;
    p = s21_strchr(str, 'e');
    if (p) *p = 'E';
  }
  return str;
}

char *s21_lgG_to_str(char *str, long double size, FORMAT *FFormat) {
  if (FFormat->tolerance < 0) FFormat->tolerance = 6;
  long double accuracy = 0.0;
  int check_work = 0, check_work_m = 0;

  long double bogomol = modfl(fabsl(size), &accuracy);
  if (fpclassify(bogomol) > 3 && fpclassify(accuracy) == 3) {
    while (truncl(bogomol * powl(10, check_work * -1)) < 1) {
      check_work--;
    }
  }
  bogomol = modfl(fabsl(size), &accuracy);
  if (fpclassify(size) > 3) {
    while (accuracy >= 1 && check_work >= 0) {
      check_work++;
      modfl(accuracy / 10, &accuracy);
    }
    if (fpclassify(bogomol) > 3) {
      for (int i = 0; i < FFormat->tolerance - check_work; i++) {
        bogomol = modfl(accuracy / 10, &accuracy);
        if (fpclassify(bogomol) > 3) {
          check_work_m++;
        }
      }
    }
  }

  int flag;
  int tolerance;
  if (check_work - 1 < -4 || check_work - 1 > FFormat->tolerance - 1) {
    flag = 1;
    tolerance = FFormat->tolerance > 0 ? FFormat->tolerance - 1 : 0;
  } else {
    flag = 0;
    if (check_work < 0)
      tolerance = FFormat->tolerance > 0 ? FFormat->tolerance : 0;
    else
      tolerance = FFormat->tolerance > 0 ? FFormat->tolerance - check_work : 0;
  }

  if (flag == 1) {
    if (FFormat->spec == 'G')
      s21_sprintf(str, FFormat->flag_sharp == 1 ? "%#.*LE" : "%.*LE", tolerance,
                  size);
    else
      s21_sprintf(str, FFormat->flag_sharp == 1 ? "%#.*Le" : "%.*Le", tolerance,
                  size);
  } else {
    s21_sprintf(str, FFormat->flag_sharp == 1 ? "%#.*Lf" : "%.*Lf", tolerance,
                size);
  }

  char *p = s21_NULL;
  if (check_work < 0 && flag == 1) {
    p = str;
    s21_size_t string_len =
        s21_strpbrk(str, FFormat->spec == 'G' ? "E" : "e") - p;
    if (string_len > 2 && (int)string_len - 1 >= FFormat->tolerance &&
        *(p + string_len - 1) == '0' && FFormat->flag_sharp == 0) {
      p = p + string_len - 1;
      while (*p == '0') {
        *(p--) = '\0';
      }
      p = str + string_len;
      s21_strcat(str, p);
    }
  }

  p = str;
  p = p + s21_strlen(str) - 1;

  while (*p == '0' && FFormat->flag_sharp != 1) {
    *p-- = '\0';
  }
  if (*p == '.' && FFormat->flag_sharp != 1) {
    *p = '\0';
  }

  return str;
}

char *s21_lf_to_str(char *str, long double size, FORMAT *FFormat) {
  if (FFormat->tolerance < 0) FFormat->tolerance = 6;
  s21_ld_to_a(str, size, FFormat);
  return str;
}

char *s21_str_from_s(char *str, va_list *argList, FORMAT *FFormat) {
  wchar_t *pw = s21_NULL;
  char *p = s21_NULL;

  switch (FFormat->len) {
    case 'l':
      pw = va_arg(*argList, wchar_t *);
      if (!pw) {
        if (FFormat->tolerance < 6)
          s21_strncat(str, "(null)", FFormat->tolerance);
        else
          s21_strcat(str, "(null)");
      } else {
        wch_to_str(str, pw, FFormat->tolerance > -1 ? FFormat->tolerance : 0);
      }
      break;
    default:
      p = va_arg(*argList, char *);
      if (!p) {
        if (FFormat->tolerance < 6)
          s21_strncat(str, "(null)", FFormat->tolerance);
        else
          s21_strcat(str, "(null)");
      } else {
        if (FFormat->tolerance > -1)
          s21_strncat(str, p, FFormat->tolerance);
        else
          s21_strcat(str, p);
      }
  }
  s21_ll_width_flag(str, FFormat);
  return str;
}

char *s21_str_from_c(char *str, va_list *argList, FORMAT *FFormat) {
  wchar_t wchar;
  wchar_t wchar_s[10] = {0};
  switch (FFormat->len) {
    case 'l':
      wchar = va_arg(*argList, wchar_t);
      wchar_s[0] = wchar;
      wch_to_str(str, wchar_s, 0);
      break;
    default:
      str[0] = va_arg(*argList, int);
      str[1] = '\0';
  }
  s21_ll_width_flag(str, FFormat);
  return str;
}

char *s21_str_from_u(char *str, va_list *argList, FORMAT *FFormat) {
  unsigned short us_size;
  unsigned long ul_size;
  unsigned int u_size;

  switch (FFormat->len) {
    case 'h':
      us_size = (unsigned short)va_arg(*argList, unsigned int);
      s21_ll_to_str(str, us_size);
      break;
    case 'l':
      ul_size = (unsigned long)va_arg(*argList, unsigned long);
      s21_ul_to_str(str, ul_size);
      break;
    default:
      u_size = (unsigned int)va_arg(*argList, unsigned int);
      s21_ll_to_str(str, u_size);
  }

  s21_ll_tolerance(str, FFormat);
  s21_sign_flag(str, FFormat);
  s21_ll_width_flag(str, FFormat);
  return str;
}

char *s21_str_from_d(char *str, va_list *argList, FORMAT *FFormat) {
  long int ld_size;
  short int sd_size;
  int size;

  switch (FFormat->len) {
    case 'h':
      sd_size = (short int)va_arg(*argList, int);
      s21_ll_to_str(str, sd_size);
      break;
    case 'l':
      ld_size = (long int)va_arg(*argList, long int);
      s21_ll_to_str(str, ld_size);
      break;
    default:
      size = va_arg(*argList, int);
      s21_ll_to_str(str, size);
  }
  s21_ll_tolerance(str, FFormat);
  s21_sign_flag(str, FFormat);
  s21_ll_width_flag(str, FFormat);
  return str;
}

char *s21_str_from_o(char *str, va_list *argList, FORMAT *FFormat) {
  unsigned long int ld_size;
  unsigned short int sd_size;
  unsigned int size;

  switch (FFormat->len) {
    case 'h':
      sd_size = (unsigned short int)va_arg(*argList, unsigned int);
      s21_ol_to_str(str, sd_size, FFormat->flag_sharp);
      break;
    case 'l':
      ld_size = (unsigned long int)va_arg(*argList, unsigned long int);
      s21_ol_to_str(str, ld_size, FFormat->flag_sharp);
      break;
    default:
      size = va_arg(*argList, unsigned int);
      s21_ol_to_str(str, size, FFormat->flag_sharp);
  }
  s21_ll_tolerance(str, FFormat);
  s21_sign_flag(str, FFormat);
  s21_ll_width_flag(str, FFormat);
  return str;
}

char *s21_str_from_xX(char *str, va_list *argList, FORMAT *FFormat) {
  unsigned long int ld_size;
  unsigned short int sd_size;
  unsigned int size;

  switch (FFormat->len) {
    case 'h':
      sd_size = (short unsigned int)va_arg(*argList, unsigned int);
      s21_hl_to_str(str, sd_size, FFormat);
      break;
    case 'l':
      ld_size = (long unsigned int)va_arg(*argList, unsigned long int);
      s21_hl_to_str(str, ld_size, FFormat);
      break;
    default:
      size = (unsigned int)va_arg(*argList, unsigned int);
      s21_hl_to_str(str, size, FFormat);
  }
  s21_ll_tolerance(str, FFormat);
  s21_sign_flag(str, FFormat);
  s21_ll_width_flag(str, FFormat);

  return str;
}

char *s21_lf_width_flag(char *str, FORMAT *FFormat) {
  int string_len = (int)s21_strlen(str);
  char *p = s21_NULL, *p2 = s21_NULL;
  p2 = str;
  if (FFormat->width > (int)string_len) {
    char *num_str = calloc(1000 + FFormat->width + 2, sizeof(char));
    if (num_str) {
      p = num_str;
      if (!is_digit(*p2) && FFormat->flag_zero) {
        *(p++) = *(p2++);
      }
      for (int i = 0; i < FFormat->width; i++) {
        if (FFormat->flag_minus == 1) {
          if (i < string_len) {
            *(p++) = *(p2++);
          } else {
            if (FFormat->flag_zero == 1)
              *(p++) = '0';
            else
              *(p++) = ' ';
          }
        } else {
          if (i < FFormat->width - string_len) {
            if (FFormat->flag_zero == 1)
              *(p++) = '0';
            else
              *(p++) = ' ';
          } else {
            *(p++) = *(p2++);
          }
        }
      }
      num_str[FFormat->width] = '\0';
      str = s21_strcpy(str, num_str);
      free(num_str);
    }
  }
  return str;
}

char *s21_ll_width_flag(char *str, FORMAT *FFormat) {
  int string_len = (int)s21_strlen(str);
  if (FFormat->width > (int)string_len) {
    char *num_str = calloc(1000 + FFormat->width + 2, sizeof(char));
    if (num_str) {
      for (int i = 0; i < FFormat->width; i++) {
        if (FFormat->flag_minus == 1) {
          if (i < string_len) {
            num_str[i] = str[i];
          } else {
            num_str[i] = ' ';
          }
        } else {
          if (i < FFormat->width - string_len) {
            num_str[i] = ' ';
          } else {
            num_str[i] = str[i - (FFormat->width - string_len)];
          }
        }
      }
      num_str[FFormat->width] = '\0';
      str = s21_strcpy(str, num_str);
      free(num_str);
    }
  }
  return str;
}

char *wch_to_str(char *str, wchar_t *wstr, s21_size_t len) {
  s21_size_t string_len = s21_strlen(str);
  int cnt = len;
  char *p = str + string_len;

  while (*wstr != '\0' && (cnt-- > 0 || len == 0)) {
    *(p++) = (char)*(wstr++);
  }
  *p = '\0';
  return str;
}
char *s21_sign_flag(char *str, FORMAT *FFormat) {
  if (is_digit(*str) || *str == 'i') {
    char num_str[2] = "";
    char *p = s21_NULL;
    p = num_str;
    if (FFormat->flag_plus)
      *(p++) = '+';
    else if (FFormat->flag_space)
      *(p++) = ' ';
    *p = '\0';
    s21_reverse_str(str);
    s21_strcat(str, num_str);
    s21_reverse_str(str);
  }
  return str;
}

char *s21_ll_tolerance(char *str, FORMAT *FFormat) {
  char *num_str = calloc(1000 + FFormat->width + 2, sizeof(char));
  if (num_str) {
    s21_size_t string_len = s21_strlen(str);
    int sdvig;
    char *p = s21_NULL;
    char *s = s21_NULL;
    p = num_str;
    s = str;

    int sign = *s == '-' ? -1 : 0;
    if (FFormat->flag_zero == 1)
      FFormat->tolerance = (FFormat->tolerance > FFormat->width)
                               ? FFormat->tolerance
                               : FFormat->width;

    FFormat->tolerance = FFormat->tolerance > (int)string_len + sign
                             ? FFormat->tolerance
                             : (int)string_len + sign;
    sdvig = FFormat->spec == 'x' && FFormat->flag_sharp == 1 ? 32 : 0;

    s21_reverse_str(str);
    for (int i = 0; i < FFormat->tolerance; i++) {
      if (i < (int)string_len + sign)
        *(p++) = *(s++);
      else
        *(p++) = '0';
    }

    if (FFormat->flag_sharp == 1 && FFormat->spec == (char)('X' + sdvig)) {
      *(p++) = (char)('X' + sdvig);
      *(p++) = '0';
    }

    if (sign < 0) *(p++) = '-';
    *p = '\0';
    s21_reverse_str(num_str);
    s21_strcpy(str, num_str);
    free(num_str);
  }
  return str;
}

char *s21_ll_to_str(char *str, long long size) {
  char *p = s21_NULL;
  int flag = 1, sign;

  sign = size < 0 ? -1 : 1;
  size *= sign;
  p = str;

  while (flag) {
    int numeral;
    if (size >= 10) {
      numeral = (int)(size % 10);
      size = (size - numeral) / 10;
    } else {
      numeral = (int)size;
      flag = 0;
    }
    *(p++) = (char)(numeral + '0');
  }

  if (sign < 0) {
    *(p++) = '-';
  }
  *p = '\0';
  s21_reverse_str(str);
  return str;
}

char *s21_ul_to_str(char *str, unsigned long long size) {
  char *p = s21_NULL;
  int flag = 1;

  p = str;

  while (flag) {
    int numeral;
    if (size >= 10) {
      numeral = (int)(size % 10);
      size = (size - numeral) / 10;
    } else {
      numeral = (int)size;
      flag = 0;
    }
    *(p++) = (char)(numeral + '0');
  }
  *p = '\0';
  s21_reverse_str(str);
  return str;
}

char *s21_ol_to_str(char *str, unsigned long long size, int prefix) {
  char *p = s21_NULL;
  int flag = 1;

  p = str;

  while (flag) {
    unsigned int numeral;
    if (size > 7) {
      numeral = size % 8;
      size = (size - numeral) / 8;
    } else {
      numeral = size;
      flag = 0;
    }
    *(p++) = (char)(numeral + '0');
  }

  if (prefix == 1) *(p++) = '0';
  *p = '\0';
  s21_reverse_str(str);
  return str;
}

char *s21_hl_to_str(char *str, unsigned long long size, FORMAT *FFormat) {
  char *p = s21_NULL;
  int flag = 1, sdvig;

  p = str;

  sdvig = FFormat->spec == 'x' ? 32 : 0;

  while (flag) {
    unsigned int numeral;
    if (size > 15) {
      numeral = size % 16;
      size = (size - numeral) / 16;
    } else {
      numeral = size;
      flag = 0;
    }
    if (numeral < 10)
      *(p++) = (char)(numeral + '0');
    else
      *(p++) = (char)(numeral + 'A' + sdvig - 10);
  }
  *p = '\0';
  s21_reverse_str(str);
  return str;
}

char *s21_str_to_int(const char *format, int *size, va_list *argList) {
  *size = 0;
  while (is_digit(*format)) {
    *size = *format - '0' + *size * 10;
    format++;
  }
  if (*format == '*') {
    *size = va_arg(*argList, int);
    format++;
  }
  return (char *)format;
}

char *s21_reverse_str(char *str) {
  s21_size_t string_len = s21_strlen(str);
  char ch;
  for (s21_size_t i = 0; i < string_len / 2; i++) {
    ch = str[i];
    str[i] = str[string_len - 1 - i];
    str[string_len - 1 - i] = ch;
  }
  return str;
}

long double s21_round(long double x, int tolerance) {
  long double accuracy = 0.0;
  long double z1 = modfl(fabsl(x), &accuracy);
  int mul = 0;
  int sign = signbit(x) == 0 ? 1 : -1;
  for (int i = 0; i < tolerance; i++) mul--;

  if (roundl(z1 / powl(10, mul)) > truncl(z1 / powl(10, mul))) {
    x = x + (5 * powl(10, mul - 1)) * sign;
  }
  if (tolerance <= 6 && z1 > 0) {
    x = x / powl(10, mul);
    x = truncl(x) * powl(10, mul);
  }
  return x;
}

char *s21_ld_to_a(char *str, long double size, FORMAT *FFormat) {
  char number1_str[1000] = "", *p1 = s21_NULL;
  p1 = number1_str;
  char number2_str[1000] = "", *p2 = s21_NULL;
  p2 = number2_str;
  long double bogomol, accuracy = 0.0L, check_work = 1.0L, check_work_t = 1.0L;
  int sign;
  sign = signbit(size) == 0 ? 1 : -1;

  if (fpclassify(size) < 4) {
    d_class_to_str(number1_str, size, FFormat->tolerance);
    if (sign < 0 && fpclassify(size) != 1) s21_strcat(str, "-");
    s21_strcat(str, number1_str);
    FFormat->flag_zero = 0;
  } else {
    size = s21_round(size, FFormat->tolerance);
    bogomol = modfl(fabsl(size), &accuracy);

    while (truncl(accuracy / check_work) > 0) {
      int numeral;
      numeral =
          (int)truncl(fmodl(truncl(accuracy), check_work * (long double)10L) /
                      (check_work));
      *(p1++) = (char)(numeral + '0');
      check_work *= 10L;
    }

    if (sign < 0) *(p1++) = '-';
    *p1 = '\0';

    for (int i = 0; i < FFormat->tolerance; i++) check_work_t *= 10;

    bogomol = roundl(bogomol * check_work_t);
    check_work = 1.0L;
    while (check_work < check_work_t) {
      int numeral;
      numeral = (int)truncl(
          fmodl(truncl(bogomol), check_work * (long double)10L) / (check_work));
      *(p2++) = (char)(numeral + '0');
      check_work *= 10L;
    }
    *p2 = '\0';
    s21_reverse_str(number1_str);
    if (s21_strlen(number1_str) == 0) s21_strcat(str, "0");
    s21_strcat(str, number1_str);
    if (FFormat->tolerance > 0 || FFormat->flag_sharp == 1)
      s21_strcat(str, ".");
    if (FFormat->tolerance > 0) {
      s21_reverse_str(number2_str);
      s21_strcat(str, number2_str);
    }
  }
  return str;
}

char *d_class_to_str(char *str, long double x, int tolerance) {
  switch (fpclassify(x)) {
    case FP_NAN:
      s21_strcat(str, "nan");
      break;
    case FP_INFINITE:
      s21_strcat(str, "inf");
      break;
    case FP_ZERO:
      s21_strcat(str, "0");
      if (tolerance > 0) {
        s21_strcat(str, ".");
        while (tolerance--) s21_strcat(str, "0");
      }
      break;
  }
  return str;
}
