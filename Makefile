.PHONY: build
all:
	g++ -std=c++14 -Werror -Wuninitialized -o build/Project3 src/*.cpp && ./build/Project3
build:
	g++ -std=c++14 -Werror -Wuninitialized -o build/Project3 src/*.cpp && ./build/Project3
