#ifndef DSP_H
#define DSP_H

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
