#include "Settings.hpp"

Settings::Settings() : playerControler{KEYBOARD, KEYBOARD}, corrnerBouncesAllowed(true){}

Controler Settings::get_playerControler(int i){return playerControler[i];}

void Settings::set_playerControler(int i, Controler c){
	playerControler[i] = c;
	if (c == MOUSE)
		playerControler[(i-1)%2] = KEYBOARD;
}