#include "display.h"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

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

void Display::draw_line(Screen screen, unsigned row, unsigned col){
  if (screen[row][col])
    SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
  else 
    SDL_SetRenderDrawColor(render, 0, 0, 0, 0);

  SDL_Rect rect = SDL_Rect {
    .x = (int) row * 20,
    .y = (int) col * 20,
    .w = 20,
    .h = 20,
  };

  SDL_RenderDrawRect(render, &rect);
  SDL_RenderFillRect(render, &rect);
}

void Display::draw(Screen screen) {
  SDL_RenderClear(render);
  for (unsigned i = 0; i < screen.size(); i++)
    for(unsigned j = 0; j < screen[0].size(); j++) 
      draw_line(screen, i, j);

  SDL_RenderPresent(render);
}


