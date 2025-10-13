#include "tests.h"

START_TEST(test_strrchr_basic) {
  char str[] = "hello world";
  char c = 'r';
  ck_assert_ptr_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

START_TEST(test_strrchr_not_found) {
  char str[] = "hello world";
  char c = 'u';
  ck_assert_ptr_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

START_TEST(test_strrchr_first_symbol) {
  char str[] = "hello world";
  char c = 'h';
  ck_assert_ptr_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

START_TEST(test_strrchr_zero_char) {
  char str[] = "hello\0world";
  char c = '\0';
  ck_assert_ptr_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

Suite *strrchr_test(void) {
  Suite *s = suite_create("\033[36ms21_strrchr\033[0m");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strrchr_basic);
  tcase_add_test(tc, test_strrchr_not_found);
  tcase_add_test(tc, test_strrchr_first_symbol);
  tcase_add_test(tc, test_strrchr_zero_char);

  suite_add_tcase(s, tc);

  return s;
}