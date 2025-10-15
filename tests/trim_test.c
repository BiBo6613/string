#include "tests.h"

START_TEST(test_trim_basic_spaces) {
  char *src = "   hello world   ";
  char *res = s21_trim(src, " ");
  ck_assert_str_eq(res, "hello world");
  free(res);
}
END_TEST

START_TEST(test_trim_tabs_newlines) {
  char *src = "\n\t hello \t\n";
  char *res = s21_trim(src, "\n\t ");
  ck_assert_str_eq(res, "hello");
  free(res);
}
END_TEST

START_TEST(test_trim_custom_chars) {
  char *src = "***test***";
  char *res = s21_trim(src, "*");
  ck_assert_str_eq(res, "test");
  free(res);
}
END_TEST

START_TEST(test_trim_all_removed) {
  char *src = "*****";
  char *res = s21_trim(src, "*");
  ck_assert_str_eq(res, "");
  free(res);
}
END_TEST

START_TEST(test_trim_no_trim_needed) {
  char *src = "hello";
  char *res = s21_trim(src, " ");
  ck_assert_str_eq(res, "hello");
  free(res);
}
END_TEST

START_TEST(test_trim_null_src) {
  char *res = s21_trim(s21_NULL, " ");
  ck_assert_ptr_eq(res, s21_NULL);
}
END_TEST

START_TEST(test_trim_null_trim_chars) {
  char *src = "   test   ";
  char *res = s21_trim(src, s21_NULL);
  ck_assert_str_eq(res, "test");
  free(res);
}
END_TEST

Suite *trim_test(void) {
  Suite *s = suite_create("\033[36ms21_trim\033[0m");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_trim_basic_spaces);
  tcase_add_test(tc, test_trim_tabs_newlines);
  tcase_add_test(tc, test_trim_custom_chars);
  tcase_add_test(tc, test_trim_all_removed);
  tcase_add_test(tc, test_trim_no_trim_needed);
  tcase_add_test(tc, test_trim_null_src);
  tcase_add_test(tc, test_trim_null_trim_chars);

  suite_add_tcase(s, tc);
  return s;
}