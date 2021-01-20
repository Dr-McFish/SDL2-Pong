#pragma once
#include <SDL2/SDL.h>

class KeyInput
{
private:
	/* data */
	const Uint8* keyState;
	Uint8 previusKeyState[512];
	Uint8 mouseState;
	Uint8 previusMouseState;
	int LENGTH;
	int Mouse_x, Mouse_y;
public:
	KeyInput();
	void update();
	bool getKey(SDL_Scancode scancode);
	bool getKeyDown(SDL_Scancode scancode);
	int get_Mouse_x();
	int get_Mouse_y();
	bool getMouse(Uint32 button);
	bool getMouseDown(Uint32 button);
};
