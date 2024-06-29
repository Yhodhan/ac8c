#include "display.h"

void sdl_error() {
  std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
  exit(EXIT_FAILURE);
}

Display::Display() {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    sdl_error();

  SDL_CreateWindowAndRenderer(1280, 640, 0, &window, &render);
  if (window == nullptr || render == nullptr)
      sdl_error();

  SDL_SetWindowTitle(window, "CHIP 8 EMULATOR");
}

Display::~Display() {
  SDL_DestroyRenderer(render);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Display::draw_line(Screen screen, unsigned x, unsigned y){
  if (screen[x][y])
    SDL_SetRenderDrawColor(render, 255, 0, 100, 255);
  else 
    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);

  SDL_Rect rect = SDL_Rect {
    .x = (int) y * 20,
    .y = (int) x * 20,
    .w = 20,
    .h = 20,
  };

  SDL_RenderDrawRect(render, &rect);
  SDL_RenderFillRect(render, &rect);
}

void Display::draw(Screen screen) {
  SDL_RenderClear(render);

  for(unsigned x = 0; x < screen.size(); ++x)
    for (unsigned y  = 0; y < screen[0].size(); ++y)
        draw_line(screen, x, y);

  SDL_RenderPresent(render);
}


