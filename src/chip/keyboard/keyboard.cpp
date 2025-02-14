#include "keyboard.h"

bool Input::is_pressed(byte key) {
    return keyboard[key];
}

void Input::set_key(byte index, bool state) {
    try {
        keyboard[index] = state;
    }
    catch(...) {
        std::cout << "Out of index" << std::endl;
    }
}
