#include "decoder.h"

Instruction decode(Opcode opcode) {
  switch (opcode.high()) {
  case 0x00:
    switch (opcode.Byte()) {
      case 0xe0: return Instruction::OP_00E0;
      case 0xee: return Instruction::OP_00EE;
      default: return Instruction::UNKNOWN;
    }
  case 0x01: return Instruction::OP_1NNN;
  case 0x02: return Instruction::OP_2NNN;
  case 0x03: return Instruction::OP_3XKK;
  case 0x04: return Instruction::OP_4XKK;
  case 0x05: return Instruction::OP_5XY0;
  case 0x06: return Instruction::OP_6XKK;
  case 0x07: return Instruction::OP_7XKK;
  case 0x08: 
    switch(opcode.low()){
      case 0x00: return Instruction::OP_8XY0;
      case 0x01: return Instruction::OP_8XY1;
      case 0x02: return Instruction::OP_8XY2;
      case 0x03: return Instruction::OP_8XY3;
      case 0x04: return Instruction::OP_8XY4;
      case 0x05: return Instruction::OP_8XY5;
      case 0x06: return Instruction::OP_8XY6;
      case 0x07: return Instruction::OP_8XY7;
      case 0x0E: return Instruction::OP_8XYE;
      default: return Instruction::UNKNOWN;
    }
  case 0x09: return Instruction::OP_9XY0;
  case 0x0A: return Instruction::OP_ANNN;
  case 0x0B: return Instruction::OP_BNNN;
  case 0x0C: return Instruction::OP_CXKK;
  case 0x0D: return Instruction::OP_DXYN;
  case 0x0E: 
    switch(opcode.Byte()){
      case 0x9E: return Instruction::OP_EX9E;
      case 0xA1: return Instruction::OP_EXA1;
      default: return Instruction::UNKNOWN;
    }
  case 0xF: 
    switch(opcode.Byte()){
      case 0x07: return Instruction::OP_FX07;
      case 0x0A: return Instruction::OP_FX0A;
      case 0x15: return Instruction::OP_FX15;
      case 0x18: return Instruction::OP_FX18;
      case 0x29: return Instruction::OP_FX29;
      case 0x33: return Instruction::OP_FX33;
      case 0x55: return Instruction::OP_FX55;
      case 0x65: return Instruction::OP_FX65;
      default: return Instruction::UNKNOWN;
    }
  default: return Instruction::UNKNOWN;
  };
}
