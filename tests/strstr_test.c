#include "tests.h"

START_TEST(test_strstr_basic) {
  char haystack[] = "hello world!";
  char needle[] = "world";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_strstr_not_found) {
  char haystack[] = "hello world!";
  char needle[] = "nellmaxo";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_strstr_first_string) {
  char haystack[] = "hello world!";
  char needle[] = "hello";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_strstr_zero_string) {
  char haystack[] = "hello \0 world!";
  char needle[] = "\0";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

Suite *strstr_test(void) {
  Suite *s = suite_create("\033[36ms21_strstr\033[0m");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strstr_basic);
  tcase_add_test(tc, test_strstr_not_found);
  tcase_add_test(tc, test_strstr_first_string);
  tcase_add_test(tc, test_strstr_zero_string);

  suite_add_tcase(s, tc);
  return s;
}