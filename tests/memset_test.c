#include "tests.h"

START_TEST(test_memset_basic) {
  char str1[20] = "Hello world";
  char str2[20] = "Hello world";

  s21_memset(str1, '*', 5);
  memset(str2, '*', 5);

  ck_assert_mem_eq(str1, str2, 20);
}
END_TEST

START_TEST(test_memset_zero_fill) {
  char str1[10] = "abcdef";
  char str2[10] = "abcdef";

  s21_memset(str1, '\0', 6);
  memset(str2, '\0', 6);

  ck_assert_mem_eq(str1, str2, 10);
}
END_TEST

START_TEST(test_memset_byte) {
  char str1[10] = "123456789";
  char str2[10] = "123456789";

  s21_memset(str1, '#', 1);
  memset(str2, '#', 1);

  ck_assert_mem_eq(str1, str2, 10);
}
END_TEST

START_TEST(test_memset_full) {
  char str1[5] = "abcd";
  char str2[5] = "abcd";

  s21_memset(str1, 'X', 4);
  memset(str2, 'X', 4);

  ck_assert_mem_eq(str1, str2, 4);
}
END_TEST

START_TEST(test_memset_binary) {
  unsigned char buf1[6] = {1, 2, 3, 4, 5, 6};
  unsigned char buf2[6] = {1, 2, 3, 4, 5, 6};

  s21_memset(buf1, 0xFF, 6);
  memset(buf2, 0xFF, 6);

  ck_assert_mem_eq(buf1, buf2, 6);
}
END_TEST

Suite *memset_test(void) {
  Suite *s = suite_create("\033[36ms21_memset\033[0m");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_memset_basic);
  tcase_add_test(tc, test_memset_zero_fill);
  tcase_add_test(tc, test_memset_byte);
  tcase_add_test(tc, test_memset_full);
  tcase_add_test(tc, test_memset_binary);

  suite_add_tcase(s, tc);
  return s;
}