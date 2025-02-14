#pragma once

#include "../../utils.h"

const static uint8_t KEYMAP[NUM_KEYS] = {
  SDLK_x, // 0
  SDLK_1, // 1
  SDLK_2, // 2
  SDLK_3, // 3
  SDLK_q, // 4
  SDLK_w, // 5
  SDLK_e, // 6
  SDLK_a, // 7
  SDLK_s, // 8
  SDLK_d, // 9
  SDLK_z, // A
  SDLK_c, // B
  SDLK_4, // C
  SDLK_r, // D
  SDLK_f, // E
  SDLK_v  // F
};

class Input {
    public:

        bool is_pressed(byte key);
        void set_key(byte index, bool state);

    private:
        std::array<bool, 0x10> keyboard = {0};
};
