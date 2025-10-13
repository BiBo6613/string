#include "tests.h"

START_TEST(test_strncmp_basic) {
  char str1[] = "hello world";
  char str2[] = "hello world";

  ck_assert_int_eq(s21_strncmp(str1, str2, 6), strncmp(str1, str2, 6));
}
END_TEST

START_TEST(test_strncmp_diff_int) {
  char str1[] = "hello world";
  char str2[] = "hello worlt";

  ck_assert_int_eq(s21_strncmp(str1, str2, 11), strncmp(str1, str2, 11));
}
END_TEST

START_TEST(test_strncmp_partial) {
  char str1[] = "abcdef";
  char str2[] = "abcxyz";

  ck_assert_int_eq(s21_strncmp(str1, str2, 6), strncmp(str1, str2, 6));
}
END_TEST

START_TEST(test_strncmp_zero_len) {
  char str1[] = "123";
  char str2[] = "456";

  ck_assert_int_eq(s21_strncmp(str1, str2, 3), strncmp(str1, str2, 3));
}
END_TEST

Suite *strncmp_test(void) {
  Suite *s = suite_create("\033[36ms21_strncmp\033[0m");
  TCase *tc = tcase_create("strncmp");

  tcase_add_test(tc, test_strncmp_basic);
  tcase_add_test(tc, test_strncmp_diff_int);
  tcase_add_test(tc, test_strncmp_partial);
  tcase_add_test(tc, test_strncmp_zero_len);

  suite_add_tcase(s, tc);
  return s;
}