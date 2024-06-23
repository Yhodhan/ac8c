#include "chip.h"

static const word OP_OFFSET = 2;
static const byte SCREEN_WIDTH = 64;
static const byte SCREEN_HEIGHT = 32;

// Sprites of Chip 8
unsigned char FONT_SET[80] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, 0x20, 0x60, 0x20, 0x20, 0x70, 0xF0, 0x10,
    0xF0, 0x80, 0xF0, 0xF0, 0x10, 0xF0, 0x10, 0xF0, 0x90, 0x90, 0xF0, 0x10,
    0x10, 0xF0, 0x80, 0xF0, 0x10, 0xF0, 0xF0, 0x80, 0xF0, 0x90, 0xF0, 0xF0,
    0x10, 0x20, 0x40, 0x40, 0xF0, 0x90, 0xF0, 0x90, 0xF0, 0xF0, 0x90, 0xF0,
    0x10, 0xF0, 0xF0, 0x90, 0xF0, 0x90, 0x90, 0xE0, 0x90, 0xE0, 0x90, 0xE0,
    0xF0, 0x80, 0x80, 0x80, 0xF0, 0xE0, 0x90, 0x90, 0x90, 0xE0, 0xF0, 0x80,
    0xF0, 0x80, 0xF0, 0xF0, 0x80, 0xF0, 0x80, 0x80,
};

Chip::Chip()
    : dt(0), st(0), sp(0), delay_timer(0), sound_timer(0), i(0), pc(0x0200),
      stack{0}, memory{0}, registers{0}, keyboard{false}, screen_drawned(false),
      key_pressed(false), key_pres_reg(0),
      _screen(std::vector<std::vector<byte>>(64, std::vector<byte>(32, 0))) {
  for (unsigned i = 0; i < 80; i++)
    memory[i] = FONT_SET[i];
}

Chip::~Chip() {}

void Chip::load_rom(std::string rom_path) {
  std::ifstream input_rom(rom_path, std::ios::binary);

  // copy data into a buffer
  std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input_rom),
                                    {});
  // copy data to chip memory
  word addr = pc;
  for (auto bin : buffer) {
    memory[addr] = bin;
    addr += 1;
  }
}

// =====================
//  Execution functions
// =====================
word Chip::fetch() { return ((memory[pc]) << 8 | memory[pc + 1]); }

void Chip::execute(Opcode opcode) {

  /*
    =============================
          OPCODE COMPOSITION
    =============================
           |      address       |
           |      |    byte     |
      high |   x  |   y  | low  |
      xxxx | xxxx | xxxx | xxxx |
    =============================
  */

  byte x = opcode.x();
  byte y = opcode.y();
  byte n = opcode.low();
  byte kk = opcode.Byte();
  word nnn = opcode.address();

  Instruction instruction = decode(opcode);

  switch (instruction) {
    case Instruction::OP_00E0: op_00e0(); break;
    case Instruction::OP_00EE: op_00ee(); break;
    case Instruction::OP_1NNN: op_1nnn(nnn); break;
    case Instruction::OP_2NNN: op_2nnn(nnn); break;
    case Instruction::OP_3XKK: op_3xkk(kk, x); break;
    case Instruction::OP_4XKK: op_4xkk(kk, x); break;
    case Instruction::OP_5XY0: op_5xy0(x, y); break;
    case Instruction::OP_6XKK: op_6xkk(kk, x); break;
    case Instruction::OP_7XKK: op_7xkk(kk, x); break;
    case Instruction::OP_8XY0: op_8xy0(x, y); break;
    case Instruction::OP_8XY1: op_8xy2(x, y); break;
    case Instruction::OP_8XY2: op_8xy2(x, y); break;
    case Instruction::OP_8XY3: op_8xy3(x, y); break;
    case Instruction::OP_8XY4: op_8xy4(x, y); break;
    case Instruction::OP_8XY5: op_8xy5(x, y); break;
    case Instruction::OP_8XY6: op_8xy6(x); break;
    case Instruction::OP_8XY7: op_8xy7(x, y); break;
    case Instruction::OP_8XYE: op_8xye(x); break;
    case Instruction::OP_9XY0: op_9xy0(x, y); break;
    case Instruction::OP_ANNN: op_annn(nnn); break;
    case Instruction::OP_BNNN: op_bnnn(nnn); break;
    case Instruction::OP_CXKK: op_cxkk(x, kk); break;
    case Instruction::OP_DXYN: op_dxyn(x, y, n); break;
    case Instruction::OP_EX9E: op_ex9e(x); break;
    case Instruction::OP_EXA1: op_exa1(x); break;
    case Instruction::OP_FX07: op_fx07(x); break;
    case Instruction::OP_FX0A: op_fx0a(x); break;
    case Instruction::OP_FX15: op_fx15(x); break;
    case Instruction::OP_FX18: op_fx18(x); break;
    case Instruction::OP_FX1E: op_fx1e(x); break;
    case Instruction::OP_FX29: op_fx29(x); break;
    case Instruction::OP_FX33: op_fx33(x); break;
    case Instruction::OP_FX55: op_fx55(x); break;
    case Instruction::OP_FX65: op_fx65(x); break;
    default: pc += OP_OFFSET;
  }
}

// ==============
//  Instructions
// ==============

// CLS - clear display
void Chip::op_00e0() {
  for (unsigned i = 0; i < _screen.size(); i++)
    fill(_screen[i].begin(), _screen[i].end(), 0);
  pc += OP_OFFSET;
}

// RET - return from a subroutine
void Chip::op_00ee() {
  sp -= 1;
  pc = stack[sp];
}

// JP - jump to location nnn
void Chip::op_1nnn(word addr) { pc = addr; }

// CALL - call subroutine at nnn
void Chip::op_2nnn(word addr) {
  stack[sp] = pc;
  sp += 1;
  pc = addr;
}

// SE - skip next instruction if vx = kk
void Chip::op_3xkk(byte kk, byte x) {
  if (registers[x] == kk)
    pc += 2 * OP_OFFSET;
  else
    pc += OP_OFFSET;
}

// SNE - skip next instruction if vx != kk
void Chip::op_4xkk(byte kk, byte x) {
  if (registers[x] != kk)
    pc += 2 * OP_OFFSET;
  else
    pc += OP_OFFSET;
}

// SE - skip next instruction if vx = vy
void Chip::op_5xy0(byte x, byte y) {
  if (registers[x] == registers[y])
    pc += 2 * OP_OFFSET;
  else
    pc += OP_OFFSET;
}

// LD - set vx = kk
void Chip::op_6xkk(byte kk, byte x) {
  registers[x] = kk;
  pc += OP_OFFSET;
}

// ADD - set vx = vx + kk
void Chip::op_7xkk(byte kk, byte x) {
  registers[x] = registers[x] + kk;
  pc += OP_OFFSET;
}

// LD - set vx = vy
void Chip::op_8xy0(byte x, byte y) {
  registers[x] = registers[y];
  pc += OP_OFFSET;
}

// OR - set vx = vx or vy
void Chip::op_8xy1(byte x, byte y) {
  registers[x] = registers[x] | registers[y];
  pc += OP_OFFSET;
}

// AND - set vx = vx and x vy
void Chip::op_8xy2(byte x, byte y) {
  registers[x] = registers[x] & registers[y];
  pc += OP_OFFSET;
}

// XOR - set vx = vx xor vy
void Chip::op_8xy3(byte x, byte y) {
  registers[x] = registers[x] ^ registers[y];
  pc += OP_OFFSET;
}

// ADD - set vx = vx + vy, set vf = carry
void Chip::op_8xy4(byte x, byte y) {
  word sum = (word)registers[x] + (word)registers[y];
  registers[0x0f] = (sum > 255);
  registers[x] = (byte)sum;
  pc += OP_OFFSET;
}

// SUB - set vx = vx - vy, set vf = not borrow
void Chip::op_8xy5(byte x, byte y) {
  registers[0x0f] = (registers[x] > registers[y]);
  registers[x] = registers[x] - registers[y];
  pc += OP_OFFSET;
}

// SHR - set vx = vx >> 1
void Chip::op_8xy6(byte x) {
  registers[0x0f] = (registers[x] & 0x01);
  registers[x] = registers[x] >> 1;
  pc += OP_OFFSET;
}

// SUBN - set vx = vx - vy, set vf = not borrow
void Chip::op_8xy7(byte x, byte y) {
  registers[0x0f] = (registers[y] > registers[x]);
  registers[x] = registers[y] - registers[x];
  pc += OP_OFFSET;
}

// SHL - set vx = vx << 1
void Chip::op_8xye(byte x) {
  registers[0x0f] = ((registers[x] & 0x80) >> 7);
  registers[x] = registers[x] << 1;
  pc += OP_OFFSET;
}

// SNE - skip next intruction if vx != vy
void Chip::op_9xy0(byte x, byte y) {
  if (registers[x] != registers[y])
    pc += 2 * OP_OFFSET;
  else
    pc += OP_OFFSET;
}

// Annn - set I = nnn
void Chip::op_annn(word addr) {
  i = addr;
  pc += OP_OFFSET;
}

// Bnnn - set I = nnn
void Chip::op_bnnn(word addr) {
  pc = (word)registers[0x0] + addr;
  pc += OP_OFFSET;
}

// RND - set vx = random byte AND kk;
void Chip::op_cxkk(byte x, byte kk) {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist(0, 255);
  auto rand = dist(rng);

  registers[x] = rand & kk;
  pc += OP_OFFSET;
}

// DRW -Display n-byte sprite starting at memory location I at (Vx, Vy), set VF
// = collision.
/*
  Steps:
  - read n bytes from memory, starting at address I.
  - for each bit of the sprite check if modifies the pixel.
  - store the bit in the screen.
*/
void Chip::op_dxyn(byte x, byte y, byte n) {
  registers[0x0f] = 0;
  for (unsigned j = 0; j <= n; j++) {
    // column y
    byte sprite = memory[this->i + j];
    byte cy = (registers[y] + j) % SCREEN_HEIGHT;
    for (unsigned bit = 0; bit < 8; bit++) {
      // line x
      byte cx = (registers[x] + j) % SCREEN_WIDTH;
      byte pixel = (sprite >> (7 - bit));
      // check if changes the pixels in the screen
      registers[0x0f] |= pixel & _screen[cy][cx];
      _screen[cx][cy] = pixel ^ _screen[cy][cx];
    }
  }
  screen_drawned = true;
  pc += OP_OFFSET;
}

// SKP - skip next instruction if key with the value of vx is pressed.
void Chip::op_ex9e(byte x) {
  byte key = registers[x];
  if (keyboard[key])
    pc += 2 * OP_OFFSET;
  else
    pc += OP_OFFSET;
}

// SKNP - skip next instruction if key with the value of vx is not pressed.
void Chip::op_exa1(byte x) {
  byte key = registers[x];
  if (!keyboard[key])
    pc += 2 * OP_OFFSET;
  else
    pc += OP_OFFSET;
}

// LD - set vx = delay timer.
void Chip::op_fx07(byte x) {
  registers[x] = delay_timer;
  pc += OP_OFFSET;
}

// LD - wait for a key press, store the value of the key in vx.
// FIX: this function is probably broken
void Chip::op_fx0a(byte x) {
  key_pressed = true;
  key_pres_reg = x;
  pc += OP_OFFSET;
}

// LD - set delay timer = vx.
void Chip::op_fx15(byte x) {
  delay_timer = registers[x];
  pc += OP_OFFSET;
}

// LD - set delay timer = vx.
void Chip::op_fx18(byte x) {
  sound_timer = registers[x];
  pc += OP_OFFSET;
}

// ADD - set i = i + vx.
void Chip::op_fx1e(byte x) {
  this->i += registers[x];
  pc += OP_OFFSET;
}

// LD - set i = location of sprite for digit vx.
void Chip::op_fx29(byte x) {
  this->i = registers[x];
  pc += OP_OFFSET;
}

// LD - store bcd ( binary-coded decimal) representation of vx in memory
// locations i, i+1, i+2.
void Chip::op_fx33(byte x) {
  byte bcd = registers[x];
  // hundreds
  byte c = bcd / 100;
  // decimals
  byte d = (bcd % 100) / 10;
  // units
  byte b = bcd % 10;
  // store values
  memory[i] = c;
  memory[i + 1] = d;
  memory[i + 2] = b;

  pc += OP_OFFSET;
}

// LD - store registers v0 to vx in memory starting at location i.
void Chip::op_fx55(byte x) {
  for (unsigned j = this->i, k = 0; j < x; j++, k++)
    memory[j] = registers[k];
  pc += OP_OFFSET;
}

// LD - store registers v0 to vx in memory starting at location i.
void Chip::op_fx65(byte x) {
  for (unsigned j = this->i, k = 0; j < x; j++, k++)
    registers[k] = memory[j];
  pc += OP_OFFSET;
}

Screen Chip::screen() { return _screen; }
