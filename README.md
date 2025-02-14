# A Chip 8 emulator in C++
the implementation of the emulator was done following the [guide](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#00E0).

## General structure
It is similar in structure to my other chip 8 emulator that is written in rust, the idea was to test the new features of C++.

## Usage 

# Linux
You need to have intalled the SDL2 and SDL2_image packages in order to compile it, Then just run 'make' in the root directory and will produce the executable in a build folder. Finally just run .build/ac8c [path_to_the_Rom]. 

# Windows
It is build with mingw toolchain, if you have installed msys2 then is it more simple as you can install the tools quite easy which are mainly 'mingw-w64-x86_64-SDL2' and 'mingw-w64-x86_64-SDL2_image'. Once they are installed then the instructions are the same than for linux.

# Roms
you can get roms to test it from the this [repo](https://github.com/kripod/chip8-roms)
