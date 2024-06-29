#include "chip/chip.h"
#include "displayer/display.h"
#include <memory>

void init(std::string rom) {
  // Init chip
  std::unique_ptr<Chip> chip(new Chip());
  chip->load_rom(rom);
  // Init display
  std::unique_ptr<Display> display(new Display);

  loop {
    Opcode opcode = chip->fetch();
    chip->execute(opcode);

    if(chip->screen_drawn())
      display->draw(chip->screen());

    SDL_Event event;
    while(SDL_PollEvent(&event)){
      if (event.type == SDL_QUIT)
        goto out;
    }
  }
  // Finish emulation
  out:
  std::cout << "Finish Emulation" << std::endl;
}

int main(int argc, char **argv) {

  if (argc < 2) {
    std::cerr << "Incorrect number of argments, rom path not provided"
              << std::endl;
    exit(EXIT_FAILURE);
  }

  init(argv[1]);
  return 0;
}
