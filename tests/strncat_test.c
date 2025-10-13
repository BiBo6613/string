#include "tests.h"

START_TEST(test_strncat_basic) {
  char s21_dest[50] = "Hello, ";
  char orig_dest[50] = "Hello, ";
  char src[] = "world!";

  ck_assert_str_eq(s21_strncat(s21_dest, src, 6), strncat(orig_dest, src, 6));
}
END_TEST

START_TEST(test_strncat_partial_copy) {
  char s21_dest[50] = "foo";
  char orig_dest[50] = "foo";
  char src[] = "barbaz";

  ck_assert_str_eq(s21_strncat(s21_dest, src, 3), strncat(orig_dest, src, 3));
}
END_TEST

START_TEST(test_strncat_zero_n) {
  char s21_dest[50] = "123";
  char orig_dest[50] = "123";
  char src[] = "abc";

  ck_assert_str_eq(s21_strncat(s21_dest, src, 0), strncat(orig_dest, src, 0));
}
END_TEST

START_TEST(test_strncat_empty_src) {
  char s21_dest[50] = "abcdef";
  char orig_dest[50] = "abcdef";
  char src[] = "";

  ck_assert_str_eq(s21_strncat(s21_dest, src, 3), strncat(orig_dest, src, 3));
}
END_TEST

START_TEST(test_strncat_with_null_inside_src) {
  char s21_dest[50] = "A";
  char orig_dest[50] = "A";
  char src[] = "B\0CDEF";

  ck_assert_str_eq(s21_strncat(s21_dest, src, 6), strncat(orig_dest, src, 6));
}
END_TEST

START_TEST(test_strncat_return_pointer) {
  char s21_dest[50] = "Return";
  char orig_dest[50] = "Return";
  char src[] = "Test";

  char *ret1 = s21_strncat(s21_dest, src, 4);
  char *ret2 = strncat(orig_dest, src, 4);

  ck_assert_ptr_eq(ret1, s21_dest);
  ck_assert_ptr_eq(ret2, orig_dest);
}
END_TEST

Suite *strncat_test(void) {
  Suite *s = suite_create("\033[36ms21_strncat\033[0m");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_strncat_basic);
  tcase_add_test(tc, test_strncat_partial_copy);
  tcase_add_test(tc, test_strncat_zero_n);
  tcase_add_test(tc, test_strncat_empty_src);
  tcase_add_test(tc, test_strncat_with_null_inside_src);
  tcase_add_test(tc, test_strncat_return_pointer);

  suite_add_tcase(s, tc);
  return s;
}
