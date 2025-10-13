#include "tests.h"

START_TEST(test_strncpy_basic) {
  char str[] = "hello world";
  char dest1[20] = {0};
  char dest2[20] = {0};

  s21_strncpy(dest1, str, 5);
  strncpy(dest2, str, 5);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strncpy_with_nulls) {
  char str[] = "hi";
  char dest1[10] = {0};
  char dest2[10] = {0};

  s21_strncpy(dest1, str, 5);
  strncpy(dest2, str, 5);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strncpy_zero_length) {
  char src[] = "test";
  char dest1[10] = "abc";
  char dest2[10] = "abc";

  s21_strncpy(dest1, src, 1);
  strncpy(dest2, src, 1);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

Suite *strncpy_test(void) {
  Suite *s = suite_create("\033[36ms21_strncpy\033[0m");
  TCase *tc = tcase_create("s21_strncpy");

  tcase_add_test(tc, test_strncpy_basic);
  tcase_add_test(tc, test_strncpy_with_nulls);
  tcase_add_test(tc, test_strncpy_zero_length);

  suite_add_tcase(s, tc);
  return s;
}