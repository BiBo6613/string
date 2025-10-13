#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);

  char *src = str;
  int printed = 0;

  while (*format) {
    if (*format == '%') {
      int count = handle_percent(&format, &args, &src);
      printed += count;
    } else {
      copy_char(&format, &src);
      printed++;
    }
  }

  *src = '\0';
  va_end(args);
  return printed;
}

int handle_percent(const char **format, va_list *args, char **src) {
  (*format)++;
  if (**format == '%') {
    *(*src)++ = *(*format)++;
    return 1;
  }

  flags_and_args spec = {0};
  parser_flags(&spec, format);
  parser_width(&spec, format, args);
  parser_accuraty(&spec, format, args);
  parser_length(&spec, format);

  char *num_start = *src;
  dispatch_specifier(&spec, format, args, src);
  *src = length_processing(&spec, *src, num_start);

  return *src - num_start;
}

void parser_flags(flags_and_args *spec, const char **format) {
  while (**format == '-' || **format == '+' || **format == ' ' ||
         **format == '0' || **format == '#') {
    switch (**format) {
      case '-':
        spec->flag_minus = true;
        break;
      case '+':
        spec->flag_plus = true;
        break;
      case ' ':
        spec->flag_space = true;
        break;
      case '0':
        spec->flag_zero = true;
        break;
      case '#':
        spec->flag_hesh = true;
        break;
    }
    (*format)++;
  }
}

void parser_width(flags_and_args *spec, const char **format, va_list *args) {
  spec->width = 0;
  while (**format >= '0' && **format <= '9') {
    spec->width = spec->width * 10 + (**format - '0');
    (*format)++;
  }
  if (**format == '*') {
    spec->width = va_arg(*args, int);
    (*format)++;
    if (spec->width < 0) {
      spec->flag_minus = true;
      spec->width = -spec->width;
    }
  }
}

void parser_accuraty(flags_and_args *spec, const char **format, va_list *args) {
  spec->accurate = -1;
  if (**format == '.') {
    (*format)++;
    spec->accurate = 0;
    while (**format >= '0' && **format <= '9') {
      spec->accurate = spec->accurate * 10 + (**format - '0');
      (*format)++;
    }
    if (**format == '*') {
      spec->accurate = va_arg(*args, int);
      (*format)++;
    }
  }
}

void parser_length(flags_and_args *spec, const char **format) {
  if (**format == 'h') {
    spec->length_h = true;
    (*format)++;
  } else if (**format == 'l') {
    spec->length_l = true;
    (*format)++;
  } else if (**format == 'L') {
    spec->length_L = true;
    (*format)++;
  }
}

void dispatch_specifier(flags_and_args *spec, const char **format,
                        va_list *args, char **src) {
  if (s21_strchr("diouxX", **format)) {
    processing_integer(format, args, src, spec);
  } else if (**format == 'c') {
    (*format)++;
    processing_char(args, src, spec);
  } else if (**format == 's') {
    (*format)++;
    processing_string(args, src, spec);
  } else if (s21_strchr("fFeEgG", **format)) {
    processing_mantissa_end_explonenta(format, args, src, spec);
  } else if (**format == 'p') {
    (*format)++;
    processing_pointer(args, src);
  }
}

void copy_char(const char **format, char **src) { *(*src)++ = *(*format)++; }

void processing_integer(const char **format, va_list *args, char **out,
                        flags_and_args *spec) {
  char spec_integer = **format;
  (*format)++;

  unsigned long long uval = 0;
  long long sval = 0;
  int notation = 10;
  int is_signed = 0;
  int uppercase = 0;

  if (spec_integer == 'd' || spec_integer == 'i') {
    is_signed = 1;
    if (spec->length_h)
      sval = (short)va_arg(*args, int);
    else if (spec->length_l)
      sval = (long)va_arg(*args, long);
    else
      sval = va_arg(*args, int);
  } else if (spec_integer == 'u') {
    if (spec->length_h)
      uval = (unsigned short)va_arg(*args, unsigned int);
    else if (spec->length_l)
      uval = (unsigned long)va_arg(*args, unsigned long);
    else
      uval = va_arg(*args, unsigned int);
  } else if (spec_integer == 'o') {
    notation = 8;
    if (spec->length_h)
      uval = (unsigned short)va_arg(*args, unsigned int);
    else if (spec->length_l)
      uval = va_arg(*args, unsigned long);
    else
      uval = va_arg(*args, unsigned int);
  } else if (spec_integer == 'x' || spec_integer == 'X') {
    notation = 16;
    uppercase = (spec_integer == 'X');
    if (spec->length_h)
      uval = (unsigned short)va_arg(*args, unsigned int);
    else if (spec->length_l)
      uval = va_arg(*args, unsigned long);
    else
      uval = va_arg(*args, unsigned int);
  }

  *out = format_integer_to_str(sval, uval, is_signed, notation, uppercase, spec,
                               *out);
}

char *format_integer_to_str(long long sval, unsigned long long uval,
                            int is_signed, int notation, int uppercase,
                            flags_and_args *spec, char *out) {
  char buf[65];
  char *p;
  int negative = 0;
  if (is_signed) {
    if (sval < 0) {
      negative = 1;
      uval = (unsigned long long)(-sval);
    } else {
      uval = (unsigned long long)sval;
    }
  }

  p = translater(uval, notation, uppercase, buf + sizeof(buf) - 1);
  int num_len = s21_strlen(p);
  int prec_zeros = 0;
  if (spec->accurate >= 0 && spec->accurate > num_len)
    prec_zeros = spec->accurate - num_len;

  if (negative)
    *out++ = '-';
  else if (spec->flag_plus && is_signed)
    *out++ = '+';
  else if (spec->flag_space && is_signed)
    *out++ = ' ';

  if (spec->flag_hesh) {
    if (notation == 16 && uval != 0) {
      *out++ = '0';
      *out++ = uppercase ? 'X' : 'x';
    } else if (notation == 8 && uval != 0) {
      *out++ = '0';
    }
  }

  while (prec_zeros-- > 0) *out++ = '0';

  while (*p) *out++ = *p++;
  return out;
}

char *translater(unsigned long long val, int base, int uppercase,
                 char *buf_end) {
  const char *digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
  *buf_end = '\0';
  char *p = buf_end;
  if (val == 0) *--p = '0';
  while (val > 0) {
    *--p = digits[val % base];
    val /= base;
  }
  return p;
}

void processing_char(va_list *args, char **src, flags_and_args *spec) {
  char ch = (char)va_arg(*args, int);
  char *num_start = *src;
  *(*src)++ = ch;
  *src = length_processing(spec, *src, num_start);
}

char *length_processing(flags_and_args *spec, char *src, char *num_start) {
  int len = src - num_start;
  int padding = spec->width - len;
  if (padding <= 0) return src;

  if (spec->flag_minus) {
    for (int i = 0; i < padding; i++) {
      *src++ = ' ';
    }
  } else {
    if (spec->flag_zero) {
      char *prefix_end = num_start;
      if (*prefix_end == '+' || *prefix_end == '-' || *prefix_end == ' ')
        prefix_end++;
      if (*prefix_end == '0' &&
          (*(prefix_end + 1) == 'x' || *(prefix_end + 1) == 'X')) {
        prefix_end += 2;
      } else if (*prefix_end == '0' && (prefix_end == num_start)) {
        prefix_end++;
      }

      int prefix_len = prefix_end - num_start;
      int move_len = len - prefix_len;

      for (int i = move_len - 1; i >= 0; i--) {
        prefix_end[i + padding] = prefix_end[i];
      }
      for (int i = 0; i < padding; i++) {
        prefix_end[i] = '0';
      }
      src += padding;
    } else {
      for (int i = len - 1; i >= 0; i--) {
        num_start[i + padding] = num_start[i];
      }
      for (int i = 0; i < padding; i++) {
        num_start[i] = ' ';
      }
      src += padding;
    }
  }

  return src;
}

void processing_string(va_list *args, char **src, flags_and_args *spec) {
  char *str = va_arg(*args, char *);
  if (!str) str = "(s21_null)";
  char *num_start = *src;
  int len = 0;
  while (str[len] && (spec->accurate < 0 || len < spec->accurate))
    *(*src)++ = str[len++];
  *src = length_processing(spec, *src, num_start);
}

void processing_mantissa_end_explonenta(const char **format, va_list *args,
                                        char **src, flags_and_args *spec) {
  char fmt = **format;
  (*format)++;
  int uppercase = (fmt == 'E' || fmt == 'G');
  long double val =
      spec->length_L ? va_arg(*args, long double) : va_arg(*args, double);
  if (val < 0) {
    *(*src)++ = '-';
    val = -val;
  } else if (spec->flag_plus)
    *(*src)++ = '+';
  else if (spec->flag_space)
    *(*src)++ = ' ';
  int precision = (spec->accurate >= 0 ? spec->accurate : 6);
  if (fmt == 'f')
    format_f(val, precision, spec, src);
  else if (fmt == 'e' || fmt == 'E')
    format_e(val, precision, uppercase, spec, src, 0);
  else if (fmt == 'g' || fmt == 'G')
    format_g(val, precision, uppercase, spec, src);
}

void format_f(long double val, int precision, flags_and_args *spec,
              char **src) {
  if (precision < 0) precision = 6;
  long double scale = powl(10.0L, precision);
  long double rounded = roundl(val * scale);
  unsigned long long ipart = (unsigned long long)(rounded / scale);
  unsigned long long frac_int =
      (unsigned long long)fabsl(fmodl(rounded, scale));

  char buf[128];
  char *p = buf + sizeof(buf);
  *--p = '\0';
  if (ipart == 0)
    *--p = '0';
  else
    while (ipart > 0) {
      *--p = '0' + (ipart % 10);
      ipart /= 10;
    }
  while (*p) *(*src)++ = *p++;

  if (precision > 0 || spec->flag_hesh) {
    *(*src)++ = '.';
    for (int i = precision - 1; i >= 0; i--) {
      unsigned long long div = (unsigned long long)powl(10, i);
      int digit = (int)(frac_int / div);
      *(*src)++ = '0' + digit;
      frac_int %= div;
    }
  }
}

void format_e(long double val, int precision, int uppercase,
              flags_and_args *spec, char **src, int is_g_format) {
  if (precision < 0) precision = 6;

  int exponent = 0;
  if (val != 0.0L) {
    exponent = (int)floorl(log10l(fabsl(val)));
    val /= powl(10.0L, exponent);
  }

  long double scale = powl(10.0L, precision);
  unsigned long long total = (unsigned long long)roundl(val * scale);
  unsigned long long int_part = total / (unsigned long long)scale;
  unsigned long long frac_int = total % (unsigned long long)scale;

  *(*src)++ = '0' + (int)int_part;

  if (precision > 0 || spec->flag_hesh || (frac_int != 0 && !is_g_format)) {
    *(*src)++ = '.';
    for (int i = precision - 1; i >= 0; i--) {
      unsigned long long div = 1;
      for (int j = 0; j < i; j++) div *= 10;
      int digit = (int)(frac_int / div);
      *(*src)++ = '0' + digit;
      frac_int %= div;
    }
  }
  *(*src)++ = uppercase ? 'E' : 'e';
  *(*src)++ = (exponent >= 0 ? '+' : '-');
  if (exponent < 0) exponent = -exponent;
  *(*src)++ = '0' + (exponent / 10);
  *(*src)++ = '0' + (exponent % 10);
}

void format_g(long double val, int precision, int uppercase,
              flags_and_args *spec, char **src) {
  if (precision == 0) precision = 1;

  int exponent = (val != 0.0L) ? (int)floorl(log10l(fabsl(val))) : 0;

  if (exponent < -4 || exponent >= precision) {
    format_e(val, precision - 1, uppercase, spec, src, 1);
    return;
  }
  int frac_digits = precision - (exponent + 1);
  if (frac_digits < 0) frac_digits = 0;
  unsigned long long int_part = (unsigned long long)val;
  long double frac = val - int_part;
  long double scale = powl(10.0L, frac_digits);
  unsigned long long frac_int = (unsigned long long)roundl(frac * scale);
  if (frac_int >= (unsigned long long)scale) {
    int_part += 1;
    frac_int = 0;
  }
  char buf[32];
  char *p = buf + sizeof(buf);
  *--p = '\0';
  if (int_part == 0)
    *--p = '0';
  else {
    unsigned long long tmp_int = int_part;
    while (tmp_int > 0) {
      *--p = '0' + (tmp_int % 10);
      tmp_int /= 10;
    }
  }
  while (*p) *(*src)++ = *p++;
  if (frac_digits > 0 || spec->flag_hesh || frac_int > 0) {
    *(*src)++ = '.';
    for (int i = frac_digits - 1; i >= 0; i--) {
      unsigned long long div = 1;
      for (int j = 0; j < i; j++) div *= 10;
      int digit = (int)(frac_int / div);
      *(*src)++ = '0' + digit;
      frac_int %= div;
    }
    if (!spec->flag_hesh) {
      char *end = *src - 1;
      while (end > *src - frac_digits - 1 && *end == '0') end--;
      *src = end + 1;
    }
  }
}

void processing_pointer(va_list *args, char **out) {
  void *ptr = va_arg(*args, void *);
  unsigned long long addr = (unsigned long long)(uintptr_t)ptr;
  char buf[2 + sizeof(void *) * 2 + 1];
  char *p = buf + sizeof(buf);
  *--p = '\0';
  if (addr == 0) *--p = '0';
  while (addr > 0) {
    int digit = addr % 16;
    *--p = "0123456789abcdef"[digit];
    addr /= 16;
  }
  *--p = 'x';
  *--p = '0';

  while (*p) *(*out)++ = *p++;
}
