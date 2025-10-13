#include "tests.h"

START_TEST(test_insert_middle) {
  char *src = "HelloWorld";
  char *str = " ";
  char *res = s21_insert(src, str, 5);
  ck_assert_str_eq(res, "Hello World");
  free(res);
}
END_TEST

START_TEST(test_insert_start) {
  char *src = "World";
  char *str = "Hello ";
  char *res = s21_insert(src, str, 0);
  ck_assert_str_eq(res, "Hello World");
  free(res);
}
END_TEST

START_TEST(test_insert_end) {
  char *src = "Hello";
  char *str = " World";
  char *res = s21_insert(src, str, 5);
  ck_assert_str_eq(res, "Hello World");
  free(res);
}
END_TEST

START_TEST(test_insert_null_input) {
  char *res1 = s21_insert(s21_NULL, "test", 0);
  char *res2 = s21_insert("test", s21_NULL, 0);
  ck_assert_ptr_eq(res1, s21_NULL);
  ck_assert_ptr_eq(res2, s21_NULL);
}
END_TEST

START_TEST(test_insert_out_of_range) {
  char *src = "Hi";
  char *str = "There";
  char *res = s21_insert(src, str, 10);  // index > len(src)
  ck_assert_ptr_eq(res, s21_NULL);
}
END_TEST

Suite *insert_test(void) {
  Suite *s = suite_create("\033[36ms21_insert\033[0m");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_insert_middle);
  tcase_add_test(tc, test_insert_start);
  tcase_add_test(tc, test_insert_end);
  tcase_add_test(tc, test_insert_null_input);
  tcase_add_test(tc, test_insert_out_of_range);

  suite_add_tcase(s, tc);
  return s;
}