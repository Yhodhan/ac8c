.PHONY: all format run clean

BUILD = build
TARGET = $(BUILD)/ac8c
SRC_DIR = src

# Find all the C++ files to compile.
SRC = $(shell find $(SRC_DIR) -name '*.cpp')
OBJS= $(patsubst %.cpp, %.o, $(SRC))

# Link library and sanitizer flags.
LIBS= --std=c++20 -lSDL2
CXXFLAGS = -g -pipe -Wall -Wformat -Werror \
           -Wextra -Wuninitialized -Winit-self -Wmaybe-uninitialized -I.

# ===================
#    TARGET RULES
# ===================

run: all
	build/ac8c roms/'tetris.ch8'

all: $(TARGET)

$(TARGET): $(OBJS)
	@ mkdir -p $(BUILD)
	$(CXX) $(LIBS) -o $@ $^

%.o : %.cpp
	$(CXX) $(LIBS) $(CXXFLAGS) -c $^ -o $@

format:
	find . -iname '*.h' -o -iname '*.cpp' | xargs clang-format -style=llvm -i

debug:
	gdb --args build/ac8c roms/'invaders.ch8'

clean:
	rm -rf $(BUILD) $(OBJS)
