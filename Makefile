.PHONY: all format run clean

BUILD = build
TARGET = $(BUILD)/ac8c
SRC_DIR = src

# Find all the C++ files to compile.
SRC = $(shell find $(SRC_DIR) -name '*.cpp')
OBJS= $(patsubst %.cpp, %.o, $(SRC))

# Link library and sanitizer flags.
LIBS= -lSDL2 -lSDL2_image 
CXXFLAGS = --std=c++20 -g -pipe -Wall -Wformat -Werror \
           -Wextra -Wuninitialized -Winit-self -Wmaybe-uninitialized -I.

# ===================
#    TARGET RULES
# ===================

run: all

all: $(TARGET)

$(TARGET): $(OBJS)
	@ mkdir -p $(BUILD)
	$(CXX) -o $@ $^ $(LIBS)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

debug:
	gdb --args build/ac8c roms/'invaders.ch8'

clean:
	rm -rf $(BUILD) $(OBJS)
