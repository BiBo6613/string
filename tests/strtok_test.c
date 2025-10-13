#include "tests.h"

START_TEST(test_strtok_basic) {
  char str1[] = "hello world test";
  char str2[] = "hello world test";
  const char delim[] = " ";

  char *token1 = s21_strtok(str1, delim);
  char *token2 = strtok(str2, delim);

  while (token1 != s21_NULL || token2 != NULL) {
    ck_assert_str_eq(token1, token2);
    token1 = s21_strtok(s21_NULL, delim);
    token2 = strtok(NULL, delim);
  }
}
END_TEST

START_TEST(test_strtok_multiple_delims) {
  char str1[] = "a,b;c d";
  char str2[] = "a,b;c d";
  const char delim[] = ",; ";

  char *token1 = s21_strtok(str1, delim);
  char *token2 = strtok(str2, delim);

  while (token1 != s21_NULL || token2 != NULL) {
    ck_assert_str_eq(token1, token2);
    token1 = s21_strtok(s21_NULL, delim);
    token2 = strtok(NULL, delim);
  }
}
END_TEST

START_TEST(test_strtok_consecutive_delims) {
  char str1[] = "hello,,world";
  char str2[] = "hello,,world";
  const char delim[] = ",";

  char *token1 = s21_strtok(str1, delim);
  char *token2 = strtok(str2, delim);

  while (token1 != s21_NULL || token2 != NULL) {
    ck_assert_str_eq(token1, token2);
    token1 = s21_strtok(s21_NULL, delim);
    token2 = strtok(NULL, delim);
  }
}
END_TEST

START_TEST(test_strtok_only_delims) {
  char str1[] = ",,,";
  char str2[] = ",,,";
  const char delim[] = ",";

  char *token1 = s21_strtok(str1, delim);
  char *token2 = strtok(str2, delim);

  ck_assert_ptr_eq(token1, s21_NULL);
  ck_assert_ptr_eq(token2, NULL);
}
END_TEST

START_TEST(test_strtok_no_delims) {
  char str1[] = "word";
  char str2[] = "word";
  const char delim[] = ",";

  char *token1 = s21_strtok(str1, delim);
  char *token2 = strtok(str2, delim);

  ck_assert_str_eq(token1, token2);
  ck_assert_ptr_eq(s21_strtok(s21_NULL, delim), strtok(NULL, delim));
}
END_TEST

Suite *strtok_test(void) {
  Suite *s = suite_create("\033[36ms21_strtok\033[0m");
  TCase *tc = tcase_create("Case");

  tcase_add_test(tc, test_strtok_basic);
  tcase_add_test(tc, test_strtok_multiple_delims);
  tcase_add_test(tc, test_strtok_consecutive_delims);
  tcase_add_test(tc, test_strtok_only_delims);
  tcase_add_test(tc, test_strtok_no_delims);

  suite_add_tcase(s, tc);
  return s;
}
