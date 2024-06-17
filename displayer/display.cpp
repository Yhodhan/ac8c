#include "display.h"

void sdl_error() {
  std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
  exit(EXIT_FAILURE);
}

Display::Display() {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    sdl_error();

  SDL_CreateWindowAndRenderer(1000, 1000, 0, &window, &render);
  if (window == nullptr || render == nullptr)
    sdl_error();

  SDL_SetWindowTitle(window, "CHIP 8 EMULATOR");
}

Display::~Display() {
  SDL_DestroyRenderer(render);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
