#include "tests.h"

START_TEST(test_memchr_found) {
  char str[] = "hello world";
  ck_assert_ptr_eq(s21_memchr(str, 'w', strlen(str)),
                   memchr(str, 'w', strlen(str)));
}
END_TEST

START_TEST(test_memchr_not_found) {
  char str[] = "hello";
  ck_assert_ptr_eq(s21_memchr(str, 'z', strlen(str)),
                   memchr(str, 'z', strlen(str)));
}
END_TEST

START_TEST(test_memchr_first_symbol) {
  char str[] = "abc";
  ck_assert_ptr_eq(s21_memchr(str, 'a', strlen(str)),
                   memchr(str, 'a', strlen(str)));
}
END_TEST

START_TEST(test_memchr_zero_char) {
  char str[] = "test\0hidden";
  ck_assert_ptr_eq(s21_memchr(str, '\0', 11), memchr(str, '\0', 11));
}
END_TEST

Suite *memchr_test(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("\033[36ms21_memchr\033[0m");
  tc = tcase_create("Core");

  tcase_add_test(tc, test_memchr_found);
  tcase_add_test(tc, test_memchr_not_found);
  tcase_add_test(tc, test_memchr_first_symbol);
  tcase_add_test(tc, test_memchr_zero_char);

  suite_add_tcase(s, tc);

  return s;
}