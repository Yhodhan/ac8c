#ifndef CHIP_H
#define CHIP_H

#include <cstdint>
#include <iostream>
#include <ostream>
#include <vector>

typedef uint8_t byte;
typedef uint16_t word;

/*
 =================
   CHIP8 EMULATOR
 =================
*/
class Chip {
public:
  Chip();
  ~Chip();

  word fetch();
  void execute(word opcode);
  void cycle();
  void op_00e0();
  void op_00ee();

private:
  /*
  ======================================================
    - rt, rd: Time and Delay registers.
    - i: Instruction register.
    - pc: Program counter.
    - sp: Stack pointer.
    - Stack: It has up to 16 addresses of space, Chip8 only allows up to 16 sub
  routines calls.
    - Memory: From 0x000 to 0x01FF Program / Data Space.
    - Registers: Chip8 has 16 8 bits registers, 0xF register usually is used to
  store flags.
    - Keyboard: It has 16-key hexadecimal layout.
  ======================================================
  */

  byte rt;
  byte rd;
  byte sp;
  word i;
  word pc;
  std::vector<word> stack;
  std::vector<byte> memory;
  std::vector<byte> registers;
  std::vector<bool> keyboard;
  std::vector<std::vector<byte>> screen;
};

#endif
