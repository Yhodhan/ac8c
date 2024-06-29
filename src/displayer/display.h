#ifndef DSP_H
#define DSP_H

#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include "../utils.h"

class Display {
  public:
    Display();
    ~Display();

    void draw(Screen screen);

  private:
    SDL_Window* window = NULL;
    SDL_Renderer* render = NULL;
    void draw_line(Screen screen, unsigned x, unsigned y);
};

#endif
