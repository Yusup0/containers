.PHONY: all clean rebuild tests check

all: tests

tests:
	mkdir -p build
	cd ./build; cmake ..
	cd ./build; cmake --build .
	./build/tests

coverage:
	mkdir -p build
	cd ./build; cmake ..;
	cd ./build; make tests_coverage
	open ./build/tests_coverage/index.html 

rebuild: clean all

clean:
	rm -rf ./build

check:
	clang-format -i -style=Google *.h
	clang-format -i -style=Google test/*.cc