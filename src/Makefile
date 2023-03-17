.PHONY: all clean rebuild tests check coverage

OS:=

ifeq ($(shell uname), Linux)
  OS=Linux
endif

ifeq ($(shell uname), Darwin)
  OS=Darwin
endif


all: tests
	./build/tests

tests:
	mkdir -p build
	cd ./build; cmake ..
	cd ./build; cmake --build .

coverage:
	mkdir -p build
	cd ./build; cmake ..;
	cd ./build; make tests_coverage
ifeq ($(OS), Linux)
	firefox ./build/tests_coverage/index.html
else
	open ./build/tests_coverage/index.html
endif

rebuild: clean all

clean:
	rm -rf ./build

check:
	clang-format -i -style=Google *.h
	clang-format -i -style=Google test/*.cc
