CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17 -g
V_COMMAND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt
L_COMMAND = leaks -atExit --

PATH_TO_TESTS = test/
PATH_TO_FUNCTIONS = functions/
COV_REPORT = report/
DOCUMENTATION = doxygen/
ROOT = functions
EXEC = s21_matrix_oop.a
EXEC_T = unit_tests

SRC = $(wildcard $(PATH_TO_FUNCTIONS)*.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))
SRC_T = $(wildcard $(PATH_TO_TESTS)*.cpp)
OBJ_T = $(patsubst %.cpp, %.o, $(SRC_T))

OS := $(shell uname -s)

all: $(EXEC) test

s21_matrix_oop.a: $(OBJ)
	ar rc $@ $(OBJ)
	ranlib $@

test: $(OBJ_T) $(EXEC)
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) $(OBJ_T) $(EXEC) -o $(PATH_TO_TESTS)$(EXEC_T) -lcheck
else
	$(CC) $(CFLAGS) $(OBJ_T) $(EXEC) -o $(PATH_TO_TESTS)$(EXEC_T) -lgtest -lgtest_main -lpthread
endif
	$(PATH_TO_TESTS)./$(EXEC_T)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

format-check:
	@cp ../materials/linters/.clang-format ./
	@clang-format -n *.h $(PATH_TO_FUNCTIONS)*.cpp $(PATH_TO_TESTS)*.cpp #$(PATH_TO_TESTS)*.h
	@rm .clang-format

format:
	@cp ../materials/linters/.clang-format ./
	@clang-format -i *.h $(PATH_TO_FUNCTIONS)*.cpp $(PATH_TO_TESTS)*.cpp #$(PATH_TO_TESTS)*.h
	@rm .clang-format

cppcheck:
	@cppcheck --enable=all --suppress=missingIncludeSystem $(PATH_TO_FUNCTIONS)*.cpp $(PATH_TO_FUNCTIONS)*.h $(PATH_TO_TESTS)*.cpp $(PATH_TO_TESTS)*.h

valgrind: test
	$(V_COMMAND) ./$(PATH_TO_TESTS)$(EXEC_T)

leaks: test
	$(L_COMMAND) ./$(PATH_TO_TESTS)$(EXEC_T)

coverage_flag:
	$(eval CFLAGS += --coverage -fprofile-arcs -ftest-coverage)

sanitize: sanitize_flag test
	./$(PATH_TO_TESTS)$(EXEC_T)

sanitize_flag:
	$(eval CFLAGS += -fsanitize=address -fsanitize=leak)

gcov_report: coverage_flag test
	gcov --no-output $(SRC_T)
	lcov --no-external --capture --directory . --output-file coverage.info
	genhtml coverage.info -o report
#	@rm -rf $(PATH_TO_TESTS)*.gcda $(PATH_TO_TESTS)*.gcno
#	@rm -rf $(ROOT)/help/*.gcda $(ROOT)/help/*.gcno
#	@rm -rf $(COV_REPORT)
#	@mkdir $(COV_REPORT)
#	@gcov -b -l -p -c $(PATH_TO_FUNCTIONS)*.gcno
#	@gcovr -o $(COV_REPORT)gcov_report.html --html --html-details
#	@rm -rf *.gcno && rm -rf *.gcda
#	@rm -rf *.info && rm -rf *.gcov

mini_verter:
	@sh mini_verter.sh

doc:
	@doxygen
	@firefox $(DOCUMENTATION)html/index.html

clean:
	@rm -rf $(PATH_TO_FUNCTIONS)*.o $(EXEC) $(PATH_TO_TESTS)*.o $(PATH_TO_TESTS)./$(EXEC_T)
	@rm -rf $(PATH_TO_FUNCTIONS)*.gcno && rm -rf $(PATH_TO_FUNCTIONS)*.gcda
	@rm -rf $(PATH_TO_FUNCTIONS)*.info && rm -rf $(PATH_TO_FUNCTIONS)*.gcov
	@rm -rf $(PATH_TO_TESTS)*.gcda $(PATH_TO_TESTS)*.gcno
	@rm -rf $(PATH_TO_TESTS)*.gcda $(PATH_TO_TESTS)*.gcno
	@rm -rf RESULT_VALGRIND.txt gcov_*
	@rm -rf $(COV_REPORT)
	@rm -rf $(DOCUMENTATION)

