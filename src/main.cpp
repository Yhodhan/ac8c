#include "chip/chip.h"
#include "displayer/display.h"
#include <chrono>
#include <thread>

void simulate_await_cycle() {
  std::this_thread::sleep_for(std::chrono::milliseconds(CLOCK_CYCLE));
}

void init_emulation(std::string rom) {
  // Init chip and display
  std::unique_ptr<Chip> chip(new Chip());
  std::unique_ptr<Display> display(new Display);

  chip->load_rom(rom);

  // Emulator loop
  loop {
    Opcode opcode = chip->fetch();
    chip->execute(opcode);

    if (chip->screen_drawn())
      display->draw(chip->screen());

    // if exit is pressed the emulation ends
    if (!chip->poll_events())
      break;

    simulate_await_cycle();
  }

  std::cout << "Finish Emulation" << std::endl;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "Incorrect number of argments, rom path not provided"
              << std::endl;
    exit(EXIT_FAILURE);
  }

  init_emulation(argv[1]);
  return 0;
}
