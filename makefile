.PHONY: format run clean all target

BUILD = build/
TARGET := build/ac8c
SRC_DIR := src/

# Find all the C++ files to compile.
SRC :=$(shell find $(SRC_DIR) -name '*.cpp')

# Link library and sanitizer flags
LIBS := --std=c++20 -lSDL2  
CXXFLAGS := -g -pipe -Wall -Wformat -Werror \
           -Wextra -Wuninitialized -Winit-self -Wmaybe-uninitialized -Os -O3 

all: target
	$(CXX) $(LIBS) $(CXXFLAGS) -o $(TARGET) $(SRC)  

target:
	mkdir -p build

format:
	find . -iname '*.h' -o -iname '*.cpp' | xargs clang-format -style=llvm -i 
	
run: 
	./ac8c chip8-roms/demos/'Maze (alt) [David Winter, 199x].ch8'

clean:
	rm -rf $(BUILD)

