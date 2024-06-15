#include "decoder.h"
// TODO: complete this function
Instruction decode(Opcode opcode) {
  switch (opcode.high()) {
  case 0x00:
    switch (opcode.Byte()) {
    case 0xe0:
      return Instruction::Op_00e0;
    }
  };

  return Instruction::Op_00e0;
}
