#include "tests.h"

START_TEST(test_to_lower_basic) {
  char *src = "HELLO WORLD";
  char *res = s21_to_lower(src);
  ck_assert_str_eq(res, "hello world");
  free(res);
}
END_TEST

START_TEST(test_to_lower_mixed) {
  char *src = "HeLLo WoRLd123";
  char *res = s21_to_lower(src);
  ck_assert_str_eq(res, "hello world123");
  free(res);
}
END_TEST

START_TEST(test_to_lower_numbers_symbols) {
  char *src = "123!@#";
  char *res = s21_to_lower(src);
  ck_assert_str_eq(res, "123!@#");
  free(res);
}
END_TEST

START_TEST(test_to_lower_empty) {
  char *src = "";
  char *res = s21_to_lower(src);
  ck_assert_str_eq(res, "");
  free(res);
}
END_TEST

START_TEST(test_to_lower_null) {
  char *res = s21_to_lower(s21_NULL);
  ck_assert_ptr_eq(res, s21_NULL);
}
END_TEST

Suite *to_lower_test(void) {
  Suite *s = suite_create("\033[36ms21_to_lower\033[0m");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_to_lower_basic);
  tcase_add_test(tc, test_to_lower_mixed);
  tcase_add_test(tc, test_to_lower_numbers_symbols);
  tcase_add_test(tc, test_to_lower_empty);
  tcase_add_test(tc, test_to_lower_null);

  suite_add_tcase(s, tc);
  return s;
}