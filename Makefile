.PHONY: all run clean

BUILD = build
TARGET = $(BUILD)/ac8c
SRC_DIR = src

# Find all the C++ files to compile.
SRC = $(shell find $(SRC_DIR) -name '*.cpp')
OBJS= $(patsubst %.cpp, %.o, $(SRC))

# Link library and sanitizer flags.
ifeq ($(OS), Windows_NT)
	LIBS= -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
else
	LIBS= -lSDL2 -lSDL2_image
endif

CXXFLAGS = --std=c++20 -pipe -Wall -Wformat -Werror \
		   -Wextra -Wuninitialized -Winit-self -Wmaybe-uninitialized -O3 -I.

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

clean:
	rm -rf $(BUILD) $(OBJS)
