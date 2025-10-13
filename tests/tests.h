#ifndef S21_STRING_TESTS
#define S21_STRING_TESTS

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

Suite *memchr_test(void);
Suite *memcmp_test(void);
Suite *memcpy_test(void);
Suite *memset_test(void);
Suite *strchr_test(void);
Suite *strncat_test(void);
Suite *strncmp_test(void);
Suite *strncpy_test(void);
Suite *strcspn_test(void);
Suite *strerror_test(void);
Suite *strlen_test(void);
Suite *strpbrk_test(void);
Suite *strrchr_test(void);
Suite *strstr_test(void);
Suite *strtok_test(void);
Suite *sprintf_test(void);
Suite *sscanf_test(void);
Suite *to_upper_test(void);
Suite *to_lower_test(void);
Suite *insert_test(void);
Suite *trim_test(void);

#endif  // S21_STRING_TESTS
