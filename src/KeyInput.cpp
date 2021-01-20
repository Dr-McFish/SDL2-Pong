#include <SDL2/SDL.h>
//#include <iostream>

#include "KeyInput.hpp"
KeyInput::KeyInput(){
	keyState = SDL_GetKeyboardState(&LENGTH);
}

void KeyInput::update(){
	for(int i = 0; i < LENGTH; i++)
		previusKeyState[i] = keyState[i];
	SDL_PumpEvents();
	previusMouseState = mouseState;
	mouseState = SDL_GetMouseState(&Mouse_x, &Mouse_y);
	Mouse_x /= 4; Mouse_y /= 4;
	//std::cout << "x:" << Mouse_x << " y:" << Mouse_y << std::endl;
}

bool KeyInput::getKey(SDL_Scancode scancode){
	return keyState[scancode];
}

bool KeyInput::getKeyDown(SDL_Scancode scancode){
	return(keyState[scancode] && !previusKeyState[scancode]);	
}

int KeyInput::get_Mouse_x(){return Mouse_x;}
int KeyInput::get_Mouse_y(){return Mouse_y;}

bool KeyInput::getMouse(Uint32 button){
	return (mouseState & SDL_BUTTON(button));
}

bool KeyInput::getMouseDown(Uint32 button){
	return (mouseState & button) && !(previusMouseState & button);
}