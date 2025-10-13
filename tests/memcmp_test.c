#include "tests.h"

START_TEST(test_memcmp_equal) {
  char str1[] = "Hello";
  char str2[] = "Hello";

  int result_s21 = s21_memcmp(str1, str2, 5);
  int result_str = memcmp(str1, str2, 5);

  ck_assert_int_eq(result_s21, result_str);
}
END_TEST

START_TEST(test_memcmp_diff_char) {
  char str1[] = "Hello";
  char str2[] = "Helli";

  ck_assert_int_eq(s21_memcmp(str1, str2, 5), memcmp(str1, str2, 5));
}
END_TEST

START_TEST(test_memcmp_partial) {
  char str1[] = "abcdef";
  char str2[] = "abcxyz";

  ck_assert_int_eq(s21_memcmp(str1, str2, 3), memcmp(str1, str2, 3));
}
END_TEST

START_TEST(test_memcmp_zero_len) {
  char str1[] = "123";
  char str2[] = "456";

  ck_assert_int_eq(s21_memcmp(str1, str2, 0), memcmp(str1, str2, 0));
}
END_TEST

Suite *memcmp_test(void) {
  Suite *s = suite_create("\033[36ms21_memcmp\033[0m");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_memcmp_equal);
  tcase_add_test(tc, test_memcmp_diff_char);
  tcase_add_test(tc, test_memcmp_partial);
  tcase_add_test(tc, test_memcmp_zero_len);

  suite_add_tcase(s, tc);
  return s;
}