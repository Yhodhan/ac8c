#include "keyboard.h"

bool Input::operator[](byte index) {
    return keyboard.at(index);
}

bool Input::is_pressed(byte key) {
    try {
        return keyboard.at(keymap.at(key));
        }
    catch(...) {
        return false;
    }
}

void Input::set_key(byte index, bool state){
    try {
        keyboard[index] = state;
    }
    catch(...) {
        std::cout << "Out of index" << std::endl;
    }
}
