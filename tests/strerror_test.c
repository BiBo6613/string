#include "tests.h"

START_TEST(test_strerror_valid_errors) {
  for (int i = 0; i < 134;
       i++) {
    char *s21_result = s21_strerror(i);
    char *orig_result = strerror(i);
    ck_assert_str_eq(s21_result, orig_result);
  }
}
END_TEST

START_TEST(test_strerror_negative_error) {
  int errnum = -5;
  char expected[64];
  sprintf(expected, "Unknown error: %d", errnum);
  ck_assert_str_eq(s21_strerror(errnum), expected);
}
END_TEST

START_TEST(test_strerror_large_error) {
  int errnum = 1000;
  char expected[64];
  sprintf(expected, "Unknown error: %d", errnum);
  ck_assert_str_eq(s21_strerror(errnum), expected);
}
END_TEST

START_TEST(test_strerror_zero) {
  int errnum = 0;
  ck_assert_str_eq(s21_strerror(errnum), strerror(errnum));
}
END_TEST

Suite *strerror_test(void) {
  Suite *s = suite_create("\033[36ms21_strerror\033[0m");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strerror_valid_errors);
  tcase_add_test(tc, test_strerror_negative_error);
  tcase_add_test(tc, test_strerror_large_error);
  tcase_add_test(tc, test_strerror_zero);

  suite_add_tcase(s, tc);
  return s;
}
