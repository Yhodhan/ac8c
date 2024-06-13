#include "chip/chip.h"
#include <memory>

int main() {
  std::unique_ptr<Chip> chip(new Chip());
  return 0;
}
