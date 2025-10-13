CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
GCOVFLAGS = -fprofile-arcs -ftest-coverage
LGFLAGS = -lcheck -lm -lpthread -lrt -lsubunit

SRC = s21_string.c s21_sprintf.c s21_sscanf.c
OBJ = $(SRC:.c=.o)
LIB = s21_string.a

TESTS = $(wildcard tests/*.c)
TEST_EXEC = unit_test
REPORT_DIR = report

all: $(LIB)

$(LIB): $(OBJ)
	@ar rcs $(LIB) $(OBJ)
	rm -f *.o
	clear
	@echo "\033[32m[OK]\033[0m \033[34mStatic library $(LIB)\033[0m"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(LIB) $(TESTS)
	@$(CC) $(CFLAGS) $(TESTS) $(LIB) -o $(TEST_EXEC) $(LGFLAGS)
	@./$(TEST_EXEC)

gcov_report: clean
	@$(CC) $(CFLAGS) $(GCOVFLAGS) $(TESTS) $(SRC) -o $(TEST_EXEC) $(LGFLAGS)
	@./$(TEST_EXEC)
	@lcov -t "s21_string" -o coverage.info -c -d .
	@genhtml -o $(REPORT_DIR) coverage.info
	clear
	@./$(TEST_EXEC)
	@echo "\033[32m[OK]\033[0m HTML-отчёт создан: \033[34m$(REPORT_DIR)/index.html\033[0m"
	google-chrome report/index.html

clean:
	rm -rf $(OBJ) $(LIB) $(TEST_EXEC) *.gcno *.gcda *.info $(REPORT_DIR)
	clear
	@echo "\033[33m[Clean]\033[0m All files delited"

rebuild: clean all
