#ifndef CHIP_H
#define CHIP_H
#include <cstdint>
#include <iostream>
#include <ostream>
#include <vector>

typedef uint8_t byte;

class Chip {
public:
  Chip();
  ~Chip();

  void print_mem();

private:
  std::vector<byte> memory;
};

#endif
