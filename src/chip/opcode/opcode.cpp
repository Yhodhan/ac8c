#include "opcode.h"

Opcode::Opcode(word op) : opcode(op) {}

byte Opcode::x() { return ((opcode & 0x0f00) >> 8); }
byte Opcode::y() { return ((opcode & 0x00f0) >> 4); }
byte Opcode::low() { return (opcode & 0x000f); }
byte Opcode::high() { return (opcode >> 12); }
word Opcode::address() { return (opcode & 0x0fff); }
uint8_t Opcode::Byte() { return (opcode & 0x00ff); }
