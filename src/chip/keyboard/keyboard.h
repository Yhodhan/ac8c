#pragma once

#include "../../utils.h"

class Input {
    public:

        bool is_pressed(byte key);
        void set_key(byte index, bool state);

    private:
        std::array<bool, 0x10> keyboard = {0};
};
