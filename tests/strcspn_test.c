#include "tests.h"

START_TEST(test_strcspn_basic) {
  ck_assert_uint_eq(s21_strcspn("abcdef", "d"), strcspn("abcdef", "d"));
}
END_TEST

START_TEST(test_strcspn_no_match) {
  ck_assert_uint_eq(s21_strcspn("abcdef", "xyz"), strcspn("abcdef", "xyz"));
}
END_TEST

START_TEST(test_strcspn_empty_str2) {
  ck_assert_uint_eq(s21_strcspn("abcdef", ""), strcspn("abcdef", ""));
}
END_TEST

START_TEST(test_strcspn_empty_str1) {
  ck_assert_uint_eq(s21_strcspn("", "abcdef"), strcspn("", "abcdef"));
}
END_TEST

START_TEST(test_strcspn_first_char_match) {
  ck_assert_uint_eq(s21_strcspn("abc", "a"), strcspn("abc", "a"));
}
END_TEST

START_TEST(test_strcspn_multiple_matches) {
  ck_assert_uint_eq(s21_strcspn("teststring", "sg"),
                    strcspn("teststring", "sg"));
}
END_TEST

Suite *strcspn_test(void) {
  Suite *s = suite_create("\033[36ms21_strcspn\033[0m");
  TCase *tc = tcase_create("strcspn_tc");

  tcase_add_test(tc, test_strcspn_basic);
  tcase_add_test(tc, test_strcspn_no_match);
  tcase_add_test(tc, test_strcspn_empty_str2);
  tcase_add_test(tc, test_strcspn_empty_str1);
  tcase_add_test(tc, test_strcspn_first_char_match);
  tcase_add_test(tc, test_strcspn_multiple_matches);

  suite_add_tcase(s, tc);
  return s;
}
