#include "tests.h"

START_TEST(test_memcpy_basic) {
  char src[] = "Hello world!";
  char dest1[50] = "";
  char dest2[50] = "";

  s21_memcpy(dest1, src, 13);
  memcpy(dest2, src, 13);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_memcpy_zero) {
  char src[] = "12345";
  char dest1[50] = "";
  char dest2[50] = "";

  s21_memcpy(dest1, src, 0);
  memcpy(dest2, src, 0);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_memcpy_partial) {
  char src[] = "abcdef";
  char dest1[10] = "zzzzzz";
  char dest2[10] = "zzzzzz";

  s21_memcpy(dest1, src, 3);
  memcpy(dest2, src, 3);

  ck_assert_mem_eq(dest1, dest2, 6);
}
END_TEST

START_TEST(test_memcpy_binary) {
  unsigned char src[] = {0, 1, 2, 3, 4, 5};
  unsigned char dest1[6] = {0};
  unsigned char dest2[6] = {0};

  s21_memcpy(dest1, src, 6);
  memcpy(dest2, src, 6);

  ck_assert_mem_eq(dest1, dest2, 6);
}
END_TEST

Suite *memcpy_test(void) {
  Suite *s = suite_create("\033[36ms21_memcpy\033[0m");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_memcpy_basic);
  tcase_add_test(tc, test_memcpy_zero);
  tcase_add_test(tc, test_memcpy_partial);
  tcase_add_test(tc, test_memcpy_binary);

  suite_add_tcase(s, tc);
  return s;
}