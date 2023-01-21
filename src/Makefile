CC=gcc
CFLAGS=-g -Wall -Werror -Wextra -std=c++17 -pedantic
GCOVFLAGS:=-fprofile-arcs -ftest-coverage 
LDFLAGS:=-lgtest -lstdc++  #-lgcov

ifeq ($(shell uname), Linux)
LDFLAGS +=-pthread -lrt -lm #-lsubunit
endif

.PHONY: all clean rebuild test gcov_report check

all: test

test: gcov_obj/containers_test.o
	$(CC) gcov_obj/containers_test.o -o $@ $(LDFLAGS) $(GCOVFLAGS)
	./test

gcov_report: rebuild
	lcov -c -d gcov_obj/. -o gcov_obj/coverage.info
	genhtml gcov_obj/coverage.info --output-directory out

gcov_obj/%.o: gcov_obj/%.cc
	$(CC) $(CFLAGS) $(GCOVFLAGS) -c $< -o $@

rebuild: clean all

clean:
	rm -f */*.o
	rm -f gcov_obj/*.gcno
	rm -f ./*.gcno
	rm -f */*.gcda
	rm -f */*.info
	rm -f gcov_obj/containers_test
	rm -f ./test
	rm -rf ./out
	rm -rf ./test.dSYM

check:
	clang-format -i -style=Google *.h
	clang-format -i -style=Google gcov_obj/*.cc
