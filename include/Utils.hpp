#pragma  once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <algorithm>
#include <iostream>
#include "Entity.hpp"

using std::string;

namespace Utils{
	void clampIn(SDL_Rect& p_screen, Entity* p_e);
	void clampOut(SDL_Rect& solid, Entity* p_e);
	void clampOut(Entity* solid_e, Entity* p_e);//Implement this well
	char checkCollision(Entity& p_e1, Entity& p_e2);
	char checkCollision(SDL_Rect& p_e1, SDL_Rect& p_e2);

	struct Timer{
		Uint32 time;
		Timer();
		Timer(Uint32 p_t);
		void restart(Uint32 p_t);
		void update(Uint32 p_dt);
		bool isDone();

	};
};