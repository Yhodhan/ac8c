#include "chip.h"

Chip::Chip(): rt(0), rd(0), sp(0), i(0), pc(0x0200),
              stack(std::vector<word> (16, 0)),
              registers(std::vector<byte> (16, 0)),
              memory(std::vector<byte> (0x1000, 0)),
              keyboard(std::vector<bool> (16, 0)),              
              screen(std::vector<std::vector<byte>>(64, std::vector<byte> (32, 0)))
             {} 
Chip::~Chip() {}

void Chip::print_mem() {
  for (auto i : this->memory)
    std::cout << i << " ";

  std::cout << std::endl;
}
