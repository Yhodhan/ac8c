#pragma once

#include "../../utils.h"

struct Opcode {
  word opcode;
  // struct constructor
  Opcode(word op);
  // methods
  byte x();
  byte y();
  byte high();
  byte low();
  uint8_t Byte();
  word address();
};
