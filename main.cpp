#include "chip/chip.h"
#include <memory>

int main(int argc, char **argv) {

  if (argc < 2) {
    std::cerr << "Incorrect number of argments, rom path not provided"
              << std::endl;
    exit(EXIT_FAILURE);
  }
  // Init chip
  std::unique_ptr<Chip> chip(new Chip());
  chip->load_rom(argv[1]);
  chip->cycle();

  return 0;
}
