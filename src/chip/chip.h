#pragma once

#include "../utils.h"
#include "keyboard/keyboard.h"
#include "decoder/decoder.h"
#include "opcode/opcode.h"

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
  void load_rom(std::string rom_path);
  void execute(Opcode opcode);
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
  void op_ex9e(byte x);
  void op_exa1(byte x);
  void op_fx07(byte x);
  void op_fx0a(byte x);
  void op_fx15(byte x);
  void op_fx18(byte x);
  void op_fx1e(byte x);
  void op_fx29(byte x);
  void op_fx33(byte x);
  void op_fx55(byte x);
  void op_fx65(byte x);
  Screen screen();
  bool screen_drawn();
  void set_key(int, bool);
  bool poll_events();

private:
  /*
    ===================================================================
      - dt: Time registers.
      - st: Time registers.
      - sp: Time registers.
      - delay_timer: value of the delay.
      - sound_timer: value of the sound.
      - i: Instruction register.
      - pc: Program counter.
      - sp: Stack pointer.
      - stack: chip8 only allows up to 16 subroutines calls.
      - memory: from 0x000 to 0x01ff is program/data space.
      - registers: chip8 has 16 8-bits registers, 0xf is flag register.
      - keyboard: it has 16-key hexadecimal layout.
      - screen: it represents the internal state of emulator screen
    ===================================================================
  */
  byte dt;
  byte st;
  byte sp;
  byte delay_timer;
  byte sound_timer;
  word i;
  word pc;
  word stack[16];
  byte memory[0x1000];
  byte registers[16];
  Input* keyboard;
  bool screen_drawned;
  bool key_pressed;
  byte key_pres_reg;
  bool paused;
  Screen _screen;
};
