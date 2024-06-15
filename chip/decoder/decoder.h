#ifndef DECODER_H
#define DECODER_H

#include "../opcode/opcode.h"

enum class Instruction {
  Op_00e0,
  Op_00ee,
  Op_1nnn,
  Op_2nnn,
  Op_3xkk,
  Op_4xkk,
  Op_5xy0,
  Op_6xkk,
  Op_7xkk,
  Op_8xy0,
  Op_8xy1,
  Op_8xy2,
  Op_8xy3,
  Op_8xy4,
  Op_8xy5,
  Op_8xy6,
  Op_8xy7,
  Op_8xye,
  Op_9xy0,
  Op_annn,
  Op_bnnn,
  Op_cxkk,
  Op_dxyn,
  Op_ex9e,
  Op_exa1,
  Op_fx07,
  Op_fx0a,
  Op_fx15,
  Op_fx18,
  Op_fx1e,
  Op_fx29,
  Op_fx33,
  Op_fx55,
  Op_fx65,
};

Instruction decode(Opcode opcode);

#endif
