PACKAGE_NAME = brick_game
VERSION = v2.0
GAME_TETRIS_VERSION = v1.0
GAME_TETRIS_NAME = tetris

GAME_SNAKE_VERSION = v1.0
GAME_SNAKE_NAME = snake

CC = gcc
LD = ld
LATEX = pdflatex
CFLAGS = -Wall -Wextra -Werror -std=c11 -g
CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -g
LDFLAGS = -lncurses
VALGRIND_COMMAND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt

MAKEFLAGS += --warn-undefined-variables
MAKEFLAGS += --no-builtin-rules

#######################
# основные директории
#######################
DIR_TESTS = test#                                      # директория с тестами
DIR_LIBS_SRC = lib/src#                                # директория с дополнительными библиотеками
DIR_LIBS = lib#                                        # папка с исходниками доп библиотек

DIR_TESTS_TETRIS = $(DIR_TESTS)/$(GAME_TETRIS_NAME)/#  # директория с тестами для tetris
DIR_TESTS_SNAKE = $(DIR_TESTS)/$(GAME_SNAKE_NAME)/#    # директория с тестами для snake

DIR_TETRIS_LIB = brick_game/tetris/#                   # исходные файлы для tetris
DIR_SNAKE_LIB = brick_game/snake/#                     # исходные файлы для snake
DIR_COMMON = brick_game/common/#                       # общие файлы

DIR_CLI = gui/cli/#                                    # директория с интерфейсом командной строки
DIR_CLI_TETRIS = $(DIR_CLI)/$(GAME_TETRIS_NAME)        # консольный интерфейс для тетриса
DIR_CLI_SNAKE = $(DIR_CLI)/$(GAME_SNAKE_NAME)          # консольный интерфейс для змейки
DIR_CLI_COMMON = $(DIR_CLI)/common                     # общие файлы для консольного интерфейса
DIR_DESKTOP = gui/desktop/#                            # директория с графическим интерфейсом программы

DIR_OBJ = obj/#                                        # директория с объектами
DIR_COV_REPORT = report/#                              # директория с отчетами о покрытии кода
DIR_DOC = doc/#                                        # директория с документацией
DIR_INSTALL = ../$(PACKAGE_NAME)/#                     # директория для установки программ
DIR_LATEX_OUT = ./$(DIR_DOC)/$(GAME_TETRIS_NAME)_doc#  # директория с документацией в формате pdf

LATEX_FLAGS = -interaction=nonstopmode -synctex=1 -output-format=pdf -output-directory=$(DIR_LATEX_OUT)

LIB_TETRIS_EXEC = s21_tetris.a#                        # библиотека с тетрисом
LIB_SNAKE_EXEC = s21_snake.a#                          # библиотека со змейкой
LIB_TETRIS_EXEC_TEST = test_$(GAME_TETRIS_NAME)#       # исполняемый файл тестов для тетриса
LIB_SNAKE_EXEC_TEST = test_$(GAME_SNAKE_NAME)#         # исполняемый файл тестов для змейки
DOC_EXEC = $(DIR_DOC)*.tex#                            # исходные файлы документации

EXTRA_LIB_EXEC = s21_matrix_oop.a#					   # библиотека с матрицами
EXTRA_LIB_NAME = s21_matrix_oop#					   # имя дополнительной библиотеки

CXXLDFLAGS = -L./Users/kimikodo/CLionProjects/CPP3_BrickGame_v2.0-1/src/$(DIR_LIBS) $(EXTRA_LIB_EXEC)#      	   # флаги для компиляции с дополнительными либами
# собираем все файлы относящиеся к тетрису
# исходники
SRC_TETRIS_LIB = $(shell find $(DIR_TETRIS_LIB) -name "*.c")
OBJ_TETRIS_LIB = $(patsubst %.c, $(DIR_OBJ)%.o, $(SRC_TETRIS_LIB))
# тесты
SRC_TEST_TETRIS_LIB = $(shell find $(DIR_TESTS_TETRIS) -name "*.c")
OBJ_TEST_TETRIS_LIB = $(patsubst %.c, $(DIR_OBJ)%.o, $(SRC_TEST_TETRIS_LIB))

# собираем файлы относящиеся к змейке
# исходники
SRC_SNAKE_LIB = $(shell find $(DIR_SNAKE_LIB) -name "*.cpp")
OBJ_SNAKE_LIB = $(patsubst %.cpp, $(DIR_OBJ)%.o, $(SRC_SNAKE_LIB))
# тесты
SRC_TEST_SNAKE_LIB = $(shell find $(DIR_TESTS_SNAKE) -name "*.cpp")
OBJ_TEST_SNAKE_LIB = $(patsubst %.cpp, $(DIR_OBJ)%.o, $(SRC_TEST_SNAKE_LIB))

# общие файлы
SRC_COMMON = $(shell find $(DIR_COMMON) -name "*.c")
OBJ_COMMON = $(patsubst %.c, $(DIR_OBJ)%.o, $(SRC_COMMON))

# исходники консольного интерфейса
SRC_CLI = $(shell find $(DIR_CLI) -name "*.c")

#
SRC_CLI_TETRIS = $(shell find $(DIR_CLI_TETRIS) -name "*.c")
OBJ_CLI_TETRIS = $(patsubst %.c, $(DIR_OBJ)%.o, $(SRC_CLI_TETRIS))

#
SRC_CLI_SNAKE = $(shell find $(DIR_CLI_SNAKE) -name "*.c")
OBJ_CLI_SNAKE = $(patsubst %.c, $(DIR_OBJ)%.o, $(SRC_CLI_SNAKE))

#
SRC_CLI_COMMON = $(shell find $(DIR_CLI_COMMON) -name "*.c")
OBJ_CLI_COMMON = $(patsubst %.c, $(DIR_OBJ)%.o, $(SRC_CLI_COMMON))

SRC_MAIN_CLI = $(shell find $(DIR_CLI) -name "main.c")
OBJ_MAIN_CLI = $(patsubst %.c, $(DIR_OBJ)%.o, $(SRC_MAIN_CLI))

CHECK_INSTALLED = $(find /usr/include /usr/local/include -name check.h)
NCURSES_INSTALLED = $(find /usr/include /usr/local/include -name ncurses.h)

vpath %.c gui/cli/%.c
vpath %.c gui/cli/tetris/%.c
vpath %.c gui/cli/common/%.c
vpath %.cpp brick_game/snake/%.cpp
vpath %.cpp src/gui/desktop/%.cpp

OS = $(shell uname -s)

.PHONY: all clean install uninstall format-check format cppcheck valgrind gcov_report leaks sanitize dvi dist

all: check_libs clean test install

s21_tetris.a: $(DIR_OBJ) $(OBJ_TETRIS_LIB) $(SRC_TETRIS_LIB) $(OBJ_COMMON)
	ar rc $@ $(OBJ_TETRIS_LIB) $(OBJ_COMMON)
	@mv $@ $(DIR_LIBS)

s21_snake.a: $(DIR_OBJ) $(OBJ_SNAKE_LIB) $(OBJ_COMMON)
	echo $(OBJ_SNAKE_LIB)
	ar rc $@ $(OBJ_SNAKE_LIB) $(OBJ_COMMON)
	@mv $@ $(DIR_LIBS)
#runlib $@

debug: $(OBJ_CLI_TETRIS)
	echo $(OBJ_CLI_TETRIS)
	@$(eval CFLAGS += -g)

uninstall: clean

dvi: $(DOC_EXEC) $(DIR_LATEX_OUT)
	@$(LATEX) $(LATEX_FLAGS) $(DOC_EXEC)

dist: clean
	@mkdir -p ../$(PACKAGE_NAME)
	tar -czvf ../$(PACKAGE_NAME)/$(PACKAGE_NAME)_$(VERSION).tar.gz ../src


install: $(DIR_OBJ) $(SRC_CLI) tetris_object snake_object $(OBJ_MAIN_CLI) $(OBJ_CLI_COMMON)
	@$(CC) -g $(DIR_OBJ)/$(GAME_TETRIS_NAME).o $(DIR_OBJ)/$(GAME_SNAKE_NAME).o $(OBJ_CLI_COMMON) $(OBJ_MAIN_CLI) -lncurses -o $(PACKAGE_NAME)_$(VERSION)
	@mkdir -p ../$(PACKAGE_NAME)
	@mv $(PACKAGE_NAME)_$(VERSION) ../$(PACKAGE_NAME)

tetris_object: s21_tetris.a $(OBJ_CLI_TETRIS) $(OBJ_CLI_COMMON)
	@$(LD) -r -o $(DIR_OBJ)/$(GAME_TETRIS_NAME).o $(OBJ_CLI_TETRIS) -L. $(DIR_LIBS)/$(LIB_TETRIS_EXEC)

snake_object: make_extra s21_snake.a $(OBJ_CLI_SNAKE) $(OBJ_CLI_COMMON)
	$(LD) -r -o $(DIR_OBJ)/$(GAME_SNAKE_NAME).o $(OBJ_CLI_SNAKE) -L. ./$(DIR_LIBS)/$(LIB_SNAKE_EXEC) ./$(DIR_LIBS)/$(EXTRA_LIB_EXEC)
#	$(CC) $(OBJ_CLI_SNAKE) $(OBJ_CLI_COMMON) $(OBJ_COMMON) -lncurses -o $(GAME_SNAKE_NAME) -L. $(LIB_SNAKE_EXEC)
#	@mkdir -p $(DIR_INSTALL)/$(GAME_SNAKE_NAME)
#	@mv $(GAME_SNAKE_NAME) $(DIR_INSTALL)$(GAME_SNAKE_NAME)/$(GAME_SNAKE_NAME)

test: test_tetris test_snake

test_tetris:  $(LIB_TETRIS_EXEC) $(OBJ_TEST_TETRIS_LIB)
	echo $(OBJ_TEST_TETRIS_LIB)
ifeq ($(OS), Darwin)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ_TEST_TETRIS_LIB) $(LIB_TETRIS_EXEC) -o $(DIR_TESTS_TETRIS)$(LIB_TETRIS_EXEC_TEST) -lcheck
else
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ_TEST_TETRIS_LIB) $(LIB_TETRIS_EXEC) -o $(DIR_TESTS_TETRIS)/$(LIB_TETRIS_EXEC_TEST) -lcheck -lsubunit -lrt -lpthread -lm
endif
	@$(DIR_TESTS_TETRIS)./$(LIB_TETRIS_EXEC_TEST)

test_snake: $(LIB_SNAKE_EXEC) $(OBJ_TEST_SNAKE_LIB)
ifeq ($(OS), Darwin)
	@$(CC) $(CXXFLAGS) $(LDFLAGS) $(OBJ_TEST_SNAKE_LIB) $(LIB_SNAKE_EXEC) -o $(DIR_TESTS_SNAKE)$(LIB_SNAKE_EXEC_TEST) -lgtest
else
	@$(CC) $(CXXFLAGS) $(LDFLAGS) $(OBJ_TEST_SNAKE_LIB) $(LIB_SNAKE_EXEC) -o $(DIR_TESTS_SNAKE)/$(LIB_SNAKE_EXEC_TEST) -lgtest -lsubunit -lrt -lpthread -lm
endif

make_extra: $(EXTRA_LIB_EXEC)

$(EXTRA_LIB_EXEC):
	sh ./scripts/buildExtraLibs.sh $(DIR_LIBS_SRC) $(EXTRA_LIB_NAME) $@
#$(shell make -C ./$(DIR_LIBS)/$(EXTRA_LIB_NAME) $@)

$(DIR_OBJ)%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(DIR_OBJ)%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)$(DIR_TETRIS_LIB)
	@mkdir -p $(DIR_OBJ)$(DIR_CLI)
	@mkdir -p $(DIR_OBJ)$(DIR_TESTS_TETRIS)
	@mkdir -p $(DIR_OBJ)$(DIR_SNAKE_LIB)
	@mkdir -p $(DIR_OBJ)$(DIR_TESTS_SNAKE)
	@mkdir -p $(DIR_OBJ)$(DIR_COMMON)
	@mkdir -p $(DIR_OBJ)$(DIR_CLI)/$(GAME_TETRIS_NAME)
	@mkdir -p $(DIR_OBJ)$(DIR_CLI)/$(GAME_SNAKE_NAME)
	@mkdir -p $(DIR_OBJ)$(DIR_CLI)/common

$(DIR_LATEX_OUT):
	@mkdir -p $(DIR_LATEX_OUT)

format-check:
	@cp ../materials/linters/.clang-format ./
	@find . -name '*.c' -o -name '*.h' | xargs clang-format -n
	@rm .clang-format

format:
	@cp ../materials/linters/.clang-format ./
	@find . -name '*.c' -o -name '*.h' | xargs clang-format -i
	@rm .clang-format

cppcheck:
	@find . -name '*.c' -o -name '*.h' | xargs cppcheck --enable=all --suppress=missingIncludeSystem

valgrind: test
	@$(VALGRIND_COMMAND) ./$(DIR_TESTS_TETRIS)/$(LIB_TETRIS_EXEC_TEST)

leaks:
	@$(L_COMMAND) ./$(DIR_TESTS_TETRIS)/$(LIB_TETRIS_EXEC_TEST)

coverage_flag:
	@$(eval CFLAGS += --coverage)

sanitize: sanitize_flag test
	@./$(DIR_TESTS_TETRIS)/$(LIB_TETRIS_EXEC_TEST)

sanitize_flag:
	@$(eval CFLAGS += -fsanitize=address -fsanitize=leak)

gcov_report: coverage_flag test
	@rm -rf $(DIR_OBJ)$(DIR_TESTS_TETRIS)*.gcda $(DIR_OBJ)$(DIR_TESTS_TETRIS)*.gcno
	@rm -rf $(DIR_COV_REPORT)
	@mkdir $(DIR_COV_REPORT)
	@gcovr -o $(DIR_COV_REPORT)gcov_report.html --html --html-details

#doc:
#	@doxygen
#	@firefox $(DOCUMENTATION)html/index.html

clean:
	@find . -name '*.gcno' -delete -o -name '*.gcda' -delete -o -name '*.gcov' -delete -o -name '*.info' -delete -o -name '*.a' -delete
	@rm -rf RESULT_VALGRIND.txt
	@rm -rf $(DIR_COV_REPORT)
	@rm -rf $(DIR_OBJ)
	@rm -rf $(LIB_TETRIS_EXEC)
	@rm -rf $(LIB_SNAKE_EXEC)
	@rm -rf $(DIR_TESTS_TETRIS)$(LIB_TETRIS_EXEC_TEST)
	@rm -rf $(DIR_INSTALL)
	@rm -rf $(PACKAGE_NAME)_$(VERSION).tar.gz

# Выводим сообщение об ошибке
.SILENT:
.PHONY: .SILENT
.SILENT: ;@:

# Обработка ошибок
ifneq ($(findstring $(MAKEFLAGS),k),)
   .IGNORE:
else
   .IGNORE: .SILENT
endif