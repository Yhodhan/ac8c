#include "chip.h"

Chip::Chip(): memory(std::vector<byte> (0x1000, 0x1)) {} 

Chip::~Chip() {}

void Chip::print_mem() {
  for (auto i : this->memory)
    std::cout << i << " ";

  std::cout << std::endl;
}
