#ifndef DSP_H
#define DSP_H

#include <cstdlib>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

class Display {
  public:
    Display();
    ~Display();

  private:
    SDL_Window* window = nullptr;
    SDL_Renderer* render = nullptr;
};

#endif
