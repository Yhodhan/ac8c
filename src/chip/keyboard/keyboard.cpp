#include "keyboard.h"

bool Input::is_pressed (byte key) {
  return keyboard[key];
}

void Input::set_key (byte index, bool state) {
  keyboard[index] = state;
}
