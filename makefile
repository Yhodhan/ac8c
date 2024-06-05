.PHONY: compile format run

CXX = g++ -std=c++20
OBJ = -o ac8c $(shell find . -iname '*.h' -o -iname '*.cpp')
FLAGS = -g -Wall -Wformat -Werror -Wextra -Wuninitialized -Winit-self -Wmaybe-uninitialized -O1 

compile:
	$(CXX) $(FLAGS) $(OBJ) 

format:
	find . -iname '*.h' -o -iname '*.cpp' | xargs clang-format -style=llvm -i 

run: 
	./ac8c
