<!-- # SDL2-Pong -->

<!-- TODO add screenshot using github image technique -->

## About

This is a pong clone written in c++ and SDL2. This is my first real project with SDL2 or even c++, so please excuse that the code is quite stinky.

## How to play

This game is unfortunately local multiplayer only : once you press `P` in the main menu to play, the left player controls their paddle up and down movement with `W` and `S`, while the player on the right can use the `up` and `down` arrows or `O` and `L` keys.

## Pre built binary

[here](bin/SDL2Pong_Windows_64bit.zip) is the pre built binary for windows

## Build instructions

### **Step 0:** Dependencies

To compile this you will need to download
 * [SDL2](https://www.libsdl.org/download-2.0.php) development library
 * [SDL2_mixer](https://www.libsdl.org/projects/SDL_mixer/) development library

### **Step 1:** git clone

First, clone the repository

	$ git clone --depth 1 https://github.com/Dr-McFish/SDL2-Pong.git SDL2-Pong && cd SDL2-Pong

### **Step 2:** Compile

Compile with with the following flags:

	-std=c++17
	-O3
	-Wall
	-m64
	-I include
	-o game.exe
	-lSDL2main
	-lSDL2
	-lSDL2_image
	-lSDL2_mixer


On Windows, also use

	-mwindows
	-lmingw32

**Note:** You may need to indicate the include paths for the SDL2 and SDL2_mixer dependencies using the `-I <dirname>` flag, as well as the lib/linker directory using `-L <dirname>` flag.

**Note:** for some god forsaken reason SDL2_mixer expects you to include <br>
`.../sdl2_folder/include/SDL2/` <br>
instead of <br>
`.../sdl2_folder/include/` <br>
so you have to include both.

For example, the command may look like something like this:

	$ g++ src/*.cpp -std=c++17 -O3 -Wall -m64 -I include -I <SDL2 include folder> -I <SDL2mixer include folder> -o game.exe -mwindows -L <SDL2 lib folder> -L <MinGW-w64 lib folder> -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer

### **Step 3:** Dynamically-Linked/Runtime libraries

To run the game, runtime libraries need to be be present inside the folder of the executable

Coppy all the `.dll`s from the `.../SDL2/bin/` and `.../SDL2_mixer/bin/` into the current folder.

### **Step 4:** (Optional) `res/` folder

If you want to delete the source files / move the executable to another location, note that the `res/` folder is needed for the game to function.

### **Step 5:** DONE!

Enjoy!