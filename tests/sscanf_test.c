#include "tests.h"

START_TEST(test_sscanf_int) {
  int a1 = 0, a2 = 0;
  char str[] = "12345";

  int n1 = s21_sscanf(str, "%d", &a1);
  int n2 = sscanf(str, "%d", &a2);

  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(test_sscanf_negative_int) {
  int a1 = 0, a2 = 0;
  char str[] = "-987";

  int n1 = s21_sscanf(str, "%d", &a1);
  int n2 = sscanf(str, "%d", &a2);

  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(test_sscanf_with_spaces) {
  int a1 = 0, a2 = 0;
  char str[] = "    42   ";

  int n1 = s21_sscanf(str, "%d", &a1);
  int n2 = sscanf(str, "%d", &a2);

  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(test_sscanf_multiple) {
  int a1 = 0, a2 = 0;
  float b1 = 0, b2 = 0;
  char str[] = "42 3.14";

  int n1 = s21_sscanf(str, "%d %f", &a1, &b1);
  int n2 = sscanf(str, "%d %f", &a2, &b2);

  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(a1, a2);
  ck_assert_float_eq_tol(b1, b2, 1e-6);
}
END_TEST

START_TEST(test_sscanf_string) {
  char s1[50], s2[50];
  char input[] = "Hello World";

  int n1 = s21_sscanf(input, "%s", s1);
  int n2 = sscanf(input, "%s", s2);

  ck_assert_int_eq(n1, n2);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_sscanf_char) {
  char c1 = 0, c2 = 0;
  char input[] = "Z";

  int n1 = s21_sscanf(input, "%c", &c1);
  int n2 = sscanf(input, "%c", &c2);

  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_sscanf_mixed) {
  int i1 = 0, i2 = 0;
  float f1 = 0, f2 = 0;
  char s1[20], s2[20];
  char input[] = "15 3.5 test";

  int n1 = s21_sscanf(input, "%d %f %s", &i1, &f1, s1);
  int n2 = sscanf(input, "%d %f %s", &i2, &f2, s2);

  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(i1, i2);
  ck_assert_float_eq_tol(f1, f2, 1e-6);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_sscanf_hex_octal) {
  int a1 = 0, a2 = 0;
  int b1 = 0, b2 = 0;
  char str[] = "0x1A 075";

  int n1 = s21_sscanf(str, "%x %o", &a1, &b1);
  int n2 = sscanf(str, "%x %o", &a2, &b2);

  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(test_sscanf_long_double) {
  long double f1 = 0, f2 = 0;
  char str[] = "123.456";

  int n1 = s21_sscanf(str, "%Lf", &f1);
  int n2 = sscanf(str, "%Lf", &f2);

  ck_assert_int_eq(n1, n2);
  ck_assert_ldouble_eq_tol(f1, f2, 1e-6);
}
END_TEST

START_TEST(test_sscanf_partial_match) {
  int a1 = 0, a2 = 0;
  float b1 = 0, b2 = 0;
  char str[] = "42 test";

  int n1 = s21_sscanf(str, "%d %f", &a1, &b1);
  int n2 = sscanf(str, "%d %f", &a2, &b2);

  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(test_sscanf_string_width) {
  char s1[10], s2[10];
  char str[] = "abcdefghij";

  int n1 = s21_sscanf(str, "%5s", s1);
  int n2 = sscanf(str, "%5s", s2);

  ck_assert_int_eq(n1, n2);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_sscanf_percent_literal) {
  char str[] = "Value: 100%";
  char s1[20], s2[20];
  int a1 = 0, a2 = 0;

  int n1 = s21_sscanf(str, "%s %d%%", s1, &a1);
  int n2 = sscanf(str, "%s %d%%", s2, &a2);

  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(a1, a2);
  ck_assert_str_eq(s1, s2);
}
END_TEST

Suite *sscanf_test(void) {
  Suite *s = suite_create("\033[36ms21_sscanf\033[0m");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_sscanf_int);
  tcase_add_test(tc, test_sscanf_negative_int);
  tcase_add_test(tc, test_sscanf_with_spaces);
  tcase_add_test(tc, test_sscanf_multiple);
  tcase_add_test(tc, test_sscanf_string);
  tcase_add_test(tc, test_sscanf_char);
  tcase_add_test(tc, test_sscanf_mixed);
  tcase_add_test(tc, test_sscanf_hex_octal);
  tcase_add_test(tc, test_sscanf_long_double);
  tcase_add_test(tc, test_sscanf_partial_match);
  tcase_add_test(tc, test_sscanf_string_width);
  tcase_add_test(tc, test_sscanf_percent_literal);

  suite_add_tcase(s, tc);
  return s;
}
