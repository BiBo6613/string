#include "s21_string.h"

int s21_sscanf(const char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int assigned = 0;

  while (*format) {
    if (isspace(*format)) {
      while (isspace(*str)) {
        str++;
      }
      format++;
      continue;
    }
    if (*format == '%') {
      format++;
      while (isspace(*str)) {
        str++;
      }
      if (*format == '%') {
        format++;
      } else {
        format_end_spec fs = parser_format(&format, &args);
        processing_specifier(&fs, &str, &args, &assigned);
      }
    } else {
      if (*str == *format) {
        str++;
      } else {
        break;
      }
      format++;
    }
  }

  va_end(args);
  return assigned;
}

// парсер
format_end_spec parser_format(const char **format, va_list *args) {
  format_end_spec spec = {0, '\0', '\0'};
  // оперелеляем ширину
  if (**format == '*') {
    spec.width = va_arg(*args, int);
    (*format)++;
  } else {
    while (isdigit((unsigned char)**format)) {
      spec.width = spec.width * 10 + (**format - '0');
      (*format)++;
    }
  }
  // определяем длину
  if (s21_strchr("hlL", **format)) {
    spec.length_mod = **format;
    (*format)++;
  }
  // определение спецификатора
  if (s21_strchr("cdieEfgGosuxXpn", **format)) {
    spec.specifier = **format;
    (*format)++;
  }
  return spec;
}

void processing_specifier(format_end_spec *fs, const char **str, va_list *args,
                          int *assigned) {
  if (s21_strchr("idouxX", fs->specifier)) {
    processing_number(fs, str, args, assigned);
  } else if (s21_strchr("eEfgG", fs->specifier)) {
    processing_double(fs, str, args, assigned);
  } else if (fs->specifier == 'c') {
    processing_char_sscanf(fs, str, args, assigned);
  } else if (fs->specifier == 's') {
    processing_string_sscanf(fs, str, args, assigned);
  }
}

void processing_number(format_end_spec *fs, const char **str, va_list *args,
                       int *assigned) {
  while (isspace(**str)) (*str)++;

  int base;

  if (fs->specifier == 'i') {
    base = 0;
  } else if (fs->specifier == 'o') {
    base = 8;
  } else if (fs->specifier == 'x' || fs->specifier == 'X') {
    base = 16;
  } else {
    base = 10;
  }
  const char *parse_start = *str;
  char *buffer = malloc((fs->width + 1) * sizeof(char));
  const char *limit = *str;
  int count = 0;
  while (*limit && (fs->width == 0 || count < fs->width)) {
    buffer[count++] = *limit++;
  }
  buffer[count] = '\0';
  char *buf_end;
  long value = s21_strtol(buffer, &buf_end, base);
  if (buf_end != buffer) {
    int parsed_len = buf_end - buffer;
    *str = parse_start + parsed_len;

    if (fs->length_mod == 'h') {
      short *dst = va_arg(*args, short *);
      *dst = (short)value;
    } else if (fs->length_mod == 'l') {
      long *dst = va_arg(*args, long *);
      *dst = (long)value;
    } else {
      int *dst = va_arg(*args, int *);
      *dst = (int)value;
    }
    (*assigned)++;
  }
  free(buffer);
}

void processing_double(format_end_spec *fs, const char **str, va_list *args,
                       int *assigned) {
  while (isspace((unsigned char)**str)) (*str)++;

  char *end;
  double value = s21_strtod(*str, &end);

  if (end != *str) {
    *str = end;
    if (fs->length_mod == 'L') {
      long double *dst = va_arg(*args, long double *);
      *dst = (long double)value;
    } else if (fs->length_mod == 'l') {
      double *dst = va_arg(*args, double *);
      *dst = (double)value;
    } else {
      float *dst = va_arg(*args, float *);
      *dst = (float)value;
    }
    (*assigned)++;
  }
}

void processing_char_sscanf(format_end_spec *fs, const char **str,
                            va_list *args, int *assigned) {
  int width = (fs->width > 0) ? fs->width : 1;
  char *dst = va_arg(*args, char *);
  int count = 0;
  while (**str && count < width) {
    dst[count] = **str;
    (*str)++;
    count++;
  }
  if (count > 0) {
    (*assigned)++;
  }
}

void processing_string_sscanf(format_end_spec *fs, const char **str,
                              va_list *args, int *assigned) {
  while (isspace((unsigned char)**str)) (*str)++;

  char *dst = va_arg(*args, char *);
  int width = (fs->width > 0) ? fs->width : INT_MAX;
  int count = 0;

  while (**str && !isspace((unsigned char)**str) && count < width) {
    dst[count++] = **str;
    (*str)++;
  }
  dst[count] = '\0';
  if (count > 0) {
    (*assigned)++;
  }
}

// s21_sscanf va s21_sprintf uchun qo'shimcha funksiyalar
long s21_strtol(const char *str, char **endptr, int base) {
  while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r' ||
         *str == '\f' || *str == '\v') {
    str++;
  }
  int sign = 1;
  if (*str == '-') {
    sign = -1;
    str++;
  } else if (*str == '+') {
    str++;
  }
  if (base == 0) {
    if (*str == '0') {
      if (*(str + 1) == 'x' || *(str + 1) == 'X') {
        base = 16;
        str += 2;
      } else {
        base = 8;
        str++;
      }
    } else {
      base = 10;
    }
  } else if (base == 16) {
    if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X')) {
      str += 2;
    }
  }
  long result = 0;
  int any = 0;
  while (*str) {
    int digit = -1;
    if (*str >= '0' && *str <= '9') {
      digit = *str - '0';
    } else if (*str >= 'a' && *str <= 'f') {
      digit = *str - 'a' + 10;
    } else if (*str >= 'A' && *str <= 'F') {
      digit = *str - 'A' + 10;
    }
    if (digit < 0 || digit >= base) break;

    result = result * base + digit;
    str++;
    any = 1;
  }
  if (endptr != s21_NULL) {
    *endptr = (char *)(any ? str : str - 1);
  }
  return result * sign;
}

const char *skip_spaces(const char *str) {
  while (s21_strchr(" \t\n\r\f\v", *str)) str++;
  return str;
}

int parse_sign(const char **str) {
  int sign = 1;
  if (**str == '-') {
    sign = -1;
    (*str)++;
  } else if (**str == '+') {
    (*str)++;
  }
  return sign;
}

double s21_strtod(const char *str, char **endptr) {
  str = skip_spaces(str);

  int sign = parse_sign(&str);
  long long int_part = 0;

  while (*str >= '0' && *str <= '9') {
    int_part = int_part * 10 + (*str - '0');
    str++;
  }

  long long frac_part = 0;
  int frac_len = 0;
  if (*str == '.') {
    str++;
    while (*str >= '0' && *str <= '9') {
      frac_part = frac_part * 10 + (*str - '0');
      frac_len++;
      str++;
    }
  }

  double value = (double)int_part;
  if (frac_len > 0) {
    value += (double)frac_part / pow(10.0, frac_len);
  }

  int exp_sign = 1;
  int exp_val = 0;
  if (*str == 'e' || *str == 'E') {
    str++;
    if (*str == '-') {
      exp_sign = -1;
      str++;
    } else if (*str == '+') {
      str++;
    }

    while (*str >= '0' && *str <= '9') {
      exp_val = exp_val * 10 + (*str - '0');
      str++;
    }
  }

  if (exp_val != 0) {
    value *= pow(10.0, exp_sign * exp_val);
  }

  value *= sign;

  if (endptr) {
    *endptr = (char *)str;
  }
  return value;
}
