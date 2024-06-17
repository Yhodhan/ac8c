.PHONY: compile format run

CXX = g++ -std=c++20
OBJ = -o ac8c $(shell find . -iname '*.h' -o -iname '*.cpp')
CFLAGS = -g -Wall -Wformat -Werror -Wextra -Wuninitialized -Winit-self -Wmaybe-uninitialized -O1 
LIBS = -lSDL2  

compile:
	$(CXX) $(LIBS) $(CFLAGS) $(OBJ) 

format:
	find . -iname '*.h' -o -iname '*.cpp' | xargs clang-format -style=llvm -i 

run: 
	./ac8c chip8-roms/demos/'Maze (alt) [David Winter, 199x].ch8'
