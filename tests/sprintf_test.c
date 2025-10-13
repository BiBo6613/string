#include "tests.h"

START_TEST(test_sprintf_char) {
  char s21_buf[100], std_buf[100];
  int s21_ret = s21_sprintf(s21_buf, "Char: %c", 'A');
  int std_ret = sprintf(std_buf, "Char: %c", 'A');
  ck_assert_int_eq(s21_ret, std_ret);
  ck_assert_str_eq(s21_buf, std_buf);
}
END_TEST

START_TEST(test_sprintf_decimal) {
  char s21_buf[100], std_buf[100];
  int s21_ret = s21_sprintf(s21_buf, "Dec: %d", -12345);
  int std_ret = sprintf(std_buf, "Dec: %d", -12345);
  ck_assert_int_eq(s21_ret, std_ret);
  ck_assert_str_eq(s21_buf, std_buf);
}
END_TEST

START_TEST(test_sprintf_integer_i) {
  char s21_buf[100], std_buf[100];
  int s21_ret = s21_sprintf(s21_buf, "Int: %i", 0x2A);
  int std_ret = sprintf(std_buf, "Int: %i", 0x2A);
  ck_assert_int_eq(s21_ret, std_ret);
  ck_assert_str_eq(s21_buf, std_buf);
}
END_TEST

START_TEST(test_sprintf_float_eE) {
  char s21_buf[100], std_buf[100];
  double val = 123.456789;
  int s21_ret = s21_sprintf(s21_buf, "e: %e | E: %E", val, val);
  int std_ret = sprintf(std_buf, "e: %e | E: %E", val, val);
  ck_assert_int_eq(s21_ret, std_ret);
  ck_assert_str_eq(s21_buf, std_buf);
}
END_TEST

START_TEST(test_sprintf_float_f) {
  char s21_buf[100], std_buf[100];
  double val = 3.14159;
  int s21_ret = s21_sprintf(s21_buf, "Pi = %.3f", val);
  int std_ret = sprintf(std_buf, "Pi = %.3f", val);
  ck_assert_int_eq(s21_ret, std_ret);
  ck_assert_str_eq(s21_buf, std_buf);
}
END_TEST

START_TEST(test_sprintf_float_gG) {
  char s21_buf[100], std_buf[100];
  double val = 12345.6789;
  int s21_ret = s21_sprintf(s21_buf, "g: %g | G: %G", val, val);
  int std_ret = sprintf(std_buf, "g: %g | G: %G", val, val);
  ck_assert_int_eq(s21_ret, std_ret);
  ck_assert_str_eq(s21_buf, std_buf);
}
END_TEST

START_TEST(test_sprintf_unsigned) {
  char s21_buf[100], std_buf[100];
  unsigned val = 4294967295u;
  int s21_ret = s21_sprintf(s21_buf, "u: %u", val);
  int std_ret = sprintf(std_buf, "u: %u", val);
  ck_assert_int_eq(s21_ret, std_ret);
  ck_assert_str_eq(s21_buf, std_buf);
}
END_TEST

START_TEST(test_sprintf_octal_hex) {
  char s21_buf[100], std_buf[100];
  unsigned val = 255;
  int s21_ret = s21_sprintf(s21_buf, "o: %#o | x: %#x | X: %#X", val, val, val);
  int std_ret = sprintf(std_buf, "o: %#o | x: %#x | X: %#X", val, val, val);
  ck_assert_int_eq(s21_ret, std_ret);
  ck_assert_str_eq(s21_buf, std_buf);
}
END_TEST

START_TEST(test_sprintf_string) {
  char s21_buf[100], std_buf[100];
  int s21_ret = s21_sprintf(s21_buf, "Str: %.5s", "HelloWorld");
  int std_ret = sprintf(std_buf, "Str: %.5s", "HelloWorld");
  ck_assert_int_eq(s21_ret, std_ret);
  ck_assert_str_eq(s21_buf, std_buf);
}
END_TEST

START_TEST(test_sprintf_pointer) {
  char s21_buf[100], std_buf[100];
  int x = 42;
  int s21_ret = s21_sprintf(s21_buf, "Ptr: %p", &x);
  int std_ret = sprintf(std_buf, "Ptr: %p", &x);
  ck_assert_int_eq(s21_ret, std_ret);
  ck_assert_str_eq(s21_buf, std_buf);
}
END_TEST

START_TEST(test_sprintf_percent) {
  char s21_buf[100], std_buf[100];
  int s21_ret = s21_sprintf(s21_buf, "100%% Done");
  int std_ret = sprintf(std_buf, "100%% Done");
  ck_assert_int_eq(s21_ret, std_ret);
  ck_assert_str_eq(s21_buf, std_buf);
}
END_TEST

START_TEST(test_sprintf_flags_and_width) {
  char s21_buf[100], std_buf[100];
  int s21_ret = s21_sprintf(s21_buf, "%+08d", 123);
  int std_ret = sprintf(std_buf, "%+08d", 123);
  ck_assert_int_eq(s21_ret, std_ret);
  ck_assert_str_eq(s21_buf, std_buf);
}
END_TEST

START_TEST(test_sprintf_precision) {
  char s21_buf[100], std_buf[100];
  int s21_ret = s21_sprintf(s21_buf, "%.5d", 42);
  int std_ret = sprintf(std_buf, "%.5d", 42);
  ck_assert_int_eq(s21_ret, std_ret);
  ck_assert_str_eq(s21_buf, std_buf);
}
END_TEST

Suite *sprintf_test(void) {
  Suite *s = suite_create("\033[36ms21_sprintf\033[0m");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_sprintf_char);
  tcase_add_test(tc, test_sprintf_decimal);
  tcase_add_test(tc, test_sprintf_integer_i);
  tcase_add_test(tc, test_sprintf_float_eE);
  tcase_add_test(tc, test_sprintf_float_f);
  tcase_add_test(tc, test_sprintf_float_gG);
  tcase_add_test(tc, test_sprintf_unsigned);
  tcase_add_test(tc, test_sprintf_octal_hex);
  tcase_add_test(tc, test_sprintf_string);
  tcase_add_test(tc, test_sprintf_pointer);
  tcase_add_test(tc, test_sprintf_percent);
  tcase_add_test(tc, test_sprintf_flags_and_width);
  tcase_add_test(tc, test_sprintf_precision);

  suite_add_tcase(s, tc);
  return s;
}
