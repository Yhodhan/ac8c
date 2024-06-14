#ifndef CHIP_H
#define CHIP_H

#include <cstdint>
#include <iostream>
#include <ostream>
#include <random>
#include <vector>

typedef uint8_t byte;
typedef uint16_t word;

#define loop                                                                   \
  for (;;)                                                                     \
    ;

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
  void op_1nnn(word addr);
  void op_2nnn(word addr);
  void op_3xkk(byte kk, byte x);
  void op_4xkk(byte kk, byte x);
  void op_5xy0(byte x, byte y);
  void op_6xkk(byte kk, byte x);
  void op_7xkk(byte kk, byte x);
  void op_8xy0(byte x, byte y);
  void op_8xy1(byte x, byte y);
  void op_8xy2(byte x, byte y);
  void op_8xy3(byte x, byte y);
  void op_8xy4(byte x, byte y);
  void op_8xy5(byte x, byte y);
  void op_8xy6(byte x);
  void op_8xy7(byte x, byte y);
  void op_8xye(byte x);
  void op_9xy0(byte x, byte y);
  void op_annn(word addr);
  void op_bnnn(word addr);
  void op_cxkk(byte x, byte kk);
  void op_dxyn(byte x, byte y, byte n);

private:
  /*
  ======================================================
    - rt, rd: Time and Delay registers.
    - i: Instruction register.
    - pc: Program counter.
    - sp: Stack pointer.
    - Stack: It has up to 16 addresses of space, Chip8 only allows up to 16
  subroutines calls.
    - Memory: From 0x000 to 0x01FF is Program/Data Space.
    - Registers: Chip8 has 16 8-bits registers, 0xF register usually is used to
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
