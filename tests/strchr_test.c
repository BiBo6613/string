#include "tests.h"

START_TEST(test_strchr_basic) {
  char str[] = "Hello";
  char c = 'l';

  ck_assert_ptr_eq(s21_strchr(str, c), strchr(str, c));
}
END_TEST

START_TEST(test_strchr_not_found) {
  char str[] = "Hello";
  char c = 'u';

  ck_assert_ptr_eq(s21_strchr(str, c), strchr(str, c));
}
END_TEST

START_TEST(test_strchr_first_symbol) {
  char str[] = "hello";
  char c = 'h';

  ck_assert_ptr_eq(s21_strchr(str, c), strchr(str, c));
}
END_TEST

START_TEST(test_strchr_zero_char) {
  char str[] = "hello\0world";
  char c = '\0';

  ck_assert_ptr_eq(s21_strchr(str, c), strchr(str, c));
}
END_TEST

Suite *strchr_test(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("\033[36ms21_strchr\033[0m");
  tc = tcase_create("Core");

  tcase_add_test(tc, test_strchr_basic);
  tcase_add_test(tc, test_strchr_not_found);
  tcase_add_test(tc, test_strchr_first_symbol);
  tcase_add_test(tc, test_strchr_zero_char);

  suite_add_tcase(s, tc);

  return s;
}