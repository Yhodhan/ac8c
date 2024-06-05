.PHONY: compile format run

CXX = g++ -std=c++20
OBJ = -o chip8 $(shell find . -iname '*.h' -o -iname '*.cpp')
FLAGS = -g -Wall -Wformat -Werror -Wextra -Wuninitialized -Winit-self -Wmaybe-uninitialized

compile:
	$(CXX) $(FLAGS) $(OBJ) 

format:
	find . -iname '*.h' -o -iname '*.cpp' | xargs clang-format -style=llvm -i 

run: 
	./chip8
