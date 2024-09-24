CC = gcc
FLAG_C = -c
ASAN = -g -fsanitize=address
FLAG_ER = -Wall -Werror -Wextra -std=c11
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes
TET_LIB_C = ./brick_game/tetris/fsm.c ./brick_game/tetris/tetris_move_logic.c ./brick_game/tetris/tetris_field_logic.c 
TET_LIB_C += ./brick_game/tetris/tetris_lib.c ./brick_game/tetris/tetris_score_logic.c ./brick_game/tetris/tetris_figure_logic.c 
TET_LIB_O = fsm.o tetris_move_logic.o tetris_field_logic.o tetris_figure_logic.o tetris_score_logic.o tetris_lib.o
TET_LIB_H = ./brick_game/tetris/fsm.h ./brick_game/tetris/tetris_logic.h ./brick_game/tetris/tetris_lib.h
CLI_C = ./gui/cli/cli.c
CLI_h = ./gui/cli/cli.h
CLI_O = cli.o
TESTS_C=test.c
TESTS_O=test.c
GCOV_FILES_DIR = gcov_files

ifeq ($(shell uname -s),Linux)
	CHECK_FLAGS = $(shell pkg-config --libs --cflags check) -lm
endif
ifeq ($(shell uname -s),Darwin)
	CHECK_FLAGS = $(shell pkg-config --libs --cflags check) -lm
endif
ifeq ($(MAC_X86), _X86_64)
	CHECK_FLAGS = $(shell pkg-config --libs --cflags check) -lm
endif


all: clean uninstall install 

install:tetris_lib.a
	gcc -Wall -Wextra -Werror -Wpedantic -o tetris tetris.c  gui/cli/cli.c tetris_lib.a -lncurses
	make clean

uninstall:
	-rm -f tetris

tetris_lib.a:
	$(CC) $(FLAG_C) $(FLAG_ER) $(TET_LIB_C)  
	ar rc tetris_lib.a $(TET_LIB_O) 
	ranlib tetris_lib.a

test: clean tetris_lib.a
	$(CC) -g --coverage $(FLAG_ER) $(TESTS_C) -o test tetris_lib.a -lcheck_pic -lm -lsubunit
	./test

gcov_report: test
	-rm -rf $(GCOV_FILES_DIR)
	-mkdir $(GCOV_FILES_DIR)
	-gcov -r test.c
	$(CC) $(FLAG_ER) $(TET_LIB_C) $(TESTS_C) --coverage -lcheck_pic -lm -lsubunit -o ./$(GCOV_FILES_DIR)/tests_result
	./$(GCOV_FILES_DIR)/tests_result
	-lcov -d $(GCOV_FILES_DIR) -t "tests_result" -o tetris.info -c -d .
	-genhtml -o report tetris.info

valgrind_test: tetris_lib.a
	$(CC) $(FLAG_C) $(FLAG_ER) $(TESTS_C) -g
	$(CC) -g $(FLAG_ER) $(FLAG_COV) -o valgrind_tests $(TET_LIB_C) $(TESTS_O) -lcheck_pic -lm -lsubunit 
	valgrind $(VALGRIND_FLAGS) ./valgrind_tests


style_test:
	cp ../materials/linters/.clang-format ./
	clang-format -n $(TET_LIB_C) $(CLI_C) $(TET_LIB_H) $(CLI_H) 
	clang-format -i $(TET_LIB_C) $(CLI_C) $(TET_LIB_H) $(CLI_H)


run: all
	./tetris


clean:
	-rm -rf *.o *.html *.gcda *.gcno *.css *.a *.gcov *.info *.out *.cfg *.txt
	-rm -f test
	-rm -f tests
	-rm -f valgrind_tests
	-rm -rf $(GCOV_FILES_DIR)
	-rm -rf report

reinstall: uninstall clean install

