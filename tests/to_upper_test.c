#include "tests.h"

START_TEST(test_to_upper_basic) {
  char *src = "hello world";
  char *res = s21_to_upper(src);
  ck_assert_str_eq(res, "HELLO WORLD");
  free(res);
}
END_TEST

START_TEST(test_to_upper_mixed) {
  char *src = "HeLLo WoRLd123";
  char *res = s21_to_upper(src);
  ck_assert_str_eq(res, "HELLO WORLD123");
  free(res);
}
END_TEST

START_TEST(test_to_upper_numbers_symbols) {
  char *src = "123!@#";
  char *res = s21_to_upper(src);
  ck_assert_str_eq(res, "123!@#");
  free(res);
}
END_TEST

START_TEST(test_to_upper_empty) {
  char *src = "";
  char *res = s21_to_upper(src);
  ck_assert_str_eq(res, "");
  free(res);
}
END_TEST

START_TEST(test_to_upper_null) {
  char *res = s21_to_upper(s21_NULL);
  ck_assert_ptr_eq(res, s21_NULL);
}
END_TEST

Suite *to_upper_test(void) {
  Suite *s = suite_create("\033[36ms21_to_upper\033[0m");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_to_upper_basic);
  tcase_add_test(tc, test_to_upper_mixed);
  tcase_add_test(tc, test_to_upper_numbers_symbols);
  tcase_add_test(tc, test_to_upper_empty);
  tcase_add_test(tc, test_to_upper_null);

  suite_add_tcase(s, tc);
  return s;
}