#include "tests.h"

#include <limits.h>

int main() {
  printf(
      "\033[33m\n  ============= s21_string_tests =============  \033[0m\n\n");

  int failed = 0;

  Suite *s21_string_tests[] = {
      memchr_test(),  memcmp_test(),   memcpy_test(),   memset_test(),
      strchr_test(),  strcspn_test(),  strncat_test(),  strncmp_test(),
      strncpy_test(), strerror_test(), strlen_test(),   strpbrk_test(),
      strrchr_test(), strstr_test(),   strtok_test(),   sprintf_test(),
      sscanf_test(),  to_upper_test(), to_lower_test(), insert_test(),
      trim_test(),    s21_NULL};

  for (int i = 0; s21_string_tests[i] != s21_NULL; i++) {
    SRunner *sr = s21_NULL;
    sr = srunner_create(s21_string_tests[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf(
      "\033[33m\n  ============= s21_string_tests =============  \033[0m\n\n");
  return failed == 0 ? 0 : 1;
}
