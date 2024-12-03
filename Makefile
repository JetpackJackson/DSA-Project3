.PHONY: all run
all:
	g++ -std=c++20 -Werror -Wuninitialized -o build/Project3 src/*.cpp
run:
	./build/Project3
