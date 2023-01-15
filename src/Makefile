CC= gcc 
CFLAGS= -Wall -Wextra -Werror -std=c11
TEST= tests/*.c
TEST_FLAGS = -lcheck
LIB_NAME = s21_matrix
OS := $(shell uname -s)
OBJ = s21_actions.c s21_arithmetic.c s21_process.c

ifeq ($(OS), Darwin)
    TEST_FLAGS = -lcheck
else
	TEST_FLAGS = -lcheck -lpthread -pthread -lrt -lm -lsubunit
endif


all: $(LIB_NAME).a

test: clean
		$(CC) $(TEST_FLAGS) $(CFLAGS) $(OBJ) $(TEST) -o test -g
		./test

gcov_report: clean
		$(CC) --coverage $(TEST_FLAGS) $(CFLAGS) $(OBJ) $(TEST) -o test
		
		./test
		lcov -t "test" -o test.info -c -d . 
		genhtml -o report test.info
		open report/index.html

clean:
	rm -rf test
	rm -rf *.a *.out *.o report *.gc* $(LIB_NAME).a *.info

run:
	./test

$(LIB_NAME).a: clean
		$(CC) $(CFLAGS) *.c -c 
		ar rcs $(LIB_NAME).a *.o

rebuild:
	make clean
	make all

leak:
	CK_FORK=no leaks --atExit -- ./test 

linter:
	cp ../materials/linters/.clang-format ..
	clang-format -i *.c *.h tests/*.c tests/*.h
	clang-format -n *.c *.h tests/*.c tests/*.h
	rm -rf ../.clang-format

