#include "tests.h"

START_TEST(test_strlen_basic) {
  char str[] = "Hello world";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_strlen_empty) {
  char str[] = "";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_strlen_one_char) {
  char str[] = "a";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_strlen_spaces) {
  char str[] = "    spaced string    ";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_strlen_with_null_char) {
  char str[] = {'H', 'e', 'l', 'l', 'o', '\0', 'X', 'Y'};
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

Suite *strlen_test(void) {
  Suite *s = suite_create("\033[36ms21_strlen\033[0m");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strlen_basic);
  tcase_add_test(tc, test_strlen_empty);
  tcase_add_test(tc, test_strlen_one_char);
  tcase_add_test(tc, test_strlen_spaces);
  tcase_add_test(tc, test_strlen_with_null_char);

  suite_add_tcase(s, tc);
  return s;
}
