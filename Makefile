.PHONY: build run
build:
	g++ -std=c++14 -Werror -Wuninitialized -o build/Project3 src/*.cpp
run:
	./build/Project3
