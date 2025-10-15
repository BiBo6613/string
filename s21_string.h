#ifndef S21_STRING_H
#define S21_STRING_H

#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define s21_NULL ((void *)0)
typedef unsigned long s21_size_t;

void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);

char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *s, int c);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);

char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *s);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *s, int c);
char *s21_strstr(const char *haystack, const char *delim);
char *s21_strtok(char *str, const char *delim);

int s21_sscanf(const char *str, const char *format, ...);
int s21_sprintf(char *str, const char *format, ...);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);

//===================================s21_sprintf====================================

typedef struct {
  int flag_minus;
  int flag_plus;
  int flag_space;
  int flag_zero;
  int flag_hesh;

  int width;
  int accurate;

  int num_system;
  char specifier_i;

  int length_h;
  int length_l;
  int length_L;
} flags_and_args;

int handle_percent(const char **format, va_list *args, char **src);
void dispatch_specifier(flags_and_args *spec, const char **format,
                        va_list *args, char **src);
void parser_flags(flags_and_args *spec, const char **format);
void parser_width(flags_and_args *spec, const char **format, va_list *args);
void parser_accuraty(flags_and_args *spec, const char **format, va_list *args);
void parser_length(flags_and_args *spec, const char **format);
void processing_integer(const char **format, va_list *args, char **out,
                        flags_and_args *spec);
char *format_integer_to_str(long long sval, unsigned long long uval,
                            int is_signed, int notation, int uppercase,
                            flags_and_args *spec, char *out);
char *translater(unsigned long long val, int base, int uppercase,
                 char *buf_end);
void processing_char(va_list *args, char **src, flags_and_args *spec);
char *length_processing(flags_and_args *spec, char *src, char *num_start);
void processing_string(va_list *args, char **src, flags_and_args *spec);
long double round_mantissa(long double value, int precision, int *exp);
void processing_mantissa_end_explonenta(const char **format, va_list *args,
                                        char **src, flags_and_args *spec);
void format_f(long double val, int precision, flags_and_args *spec, char **src);
void format_e(long double val, int precision, int uppercase,
              flags_and_args *spec, char **src, int is_g_format);
void format_g(long double val, int precision, int uppercase,
              flags_and_args *spec, char **src);
void processing_pointer(va_list *args, char **out);
void copy_char(const char **format, char **src);

//===================================s21_sscanf====================================

typedef struct {
  int width;
  char length_mod;
  char specifier;
} format_end_spec;

format_end_spec parser_format(const char **format, va_list *args);
void processing_specifier(format_end_spec *fs, const char **str, va_list *args,
                          int *assigned);
void processing_number(format_end_spec *fs, const char **str, va_list *args,
                       int *assigned);
void processing_double(format_end_spec *fs, const char **str, va_list *args,
                       int *assigned);
void processing_char_sscanf(format_end_spec *fs, const char **str,
                            va_list *args, int *assigned);
void processing_string_sscanf(format_end_spec *fs, const char **str,
                              va_list *args, int *assigned);
char *s21_strchr(const char *str, int c);
long s21_strtol(const char *str, char **endptr, int base);
double s21_strtod(const char *str, char **endptr);
const char *skip_spaces(const char *str);
int parse_sign(const char **str);

#endif  // S21_STRING_H
