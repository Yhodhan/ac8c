#ifndef OPCODE_H
#define OPCODE_H

#include <cstdint>

typedef uint8_t byte;
typedef uint16_t word;

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

#endif
