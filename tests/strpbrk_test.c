#include "tests.h"

START_TEST(test_strpbrk_basic) {
  char str1[] = "hello world";
  char str2[] = "world";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(test_strpbrk_no_match) {
  char str1[] = "hello world";
  char str2[] = "ztu";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(test_strpbrk_empty_patern) {
  char str1[] = "hello world";
  char str2[] = "";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(test_strpbrk_empty_source) {
  char str1[] = "";
  char str2[] = "hello";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

Suite *strpbrk_test(void) {
  Suite *s = suite_create("\033[36ms21_strpbrk\033[0m");
  TCase *tc = tcase_create("Case");

  tcase_add_test(tc, test_strpbrk_basic);
  tcase_add_test(tc, test_strpbrk_no_match);
  tcase_add_test(tc, test_strpbrk_empty_patern);
  tcase_add_test(tc, test_strpbrk_empty_source);

  suite_add_tcase(s, tc);
  return s;
}
