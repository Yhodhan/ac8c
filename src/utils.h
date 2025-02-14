#include <cstdlib>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <array>

#define loop for (;;)
#define Screen std::vector<std::vector<byte>>
typedef uint8_t byte;
typedef uint16_t word;
#define NUM_KEYS 16
