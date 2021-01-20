#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <algorithm>
#include <iostream>
#include "Entity.hpp"

#include "Utils.hpp"


void Utils::clampIn(SDL_Rect& p_screen, Entity* p_e){
	p_e->set_x( std::min(std::max((int)p_e->get_x(), p_screen.x), (p_screen.x + p_screen.w - p_e->get_currentFrame().w))  );
	p_e->set_y( std::min(std::max((int)p_e->get_y(), p_screen.y), (p_screen.y + p_screen.h - p_e->get_currentFrame().h))  );
}

//...-1-...
//  2-+-3
//'''-4-'''		----0: no collision
char Utils::checkCollision(Entity& p_e1, Entity& p_e2) {
	//stolen from
	//https://gamedev.stackexchange.com/a/29796
	//I am not even using this in the final product *facepalm*
	SDL_Rect r_e1 = p_e1.get_currentFrame();
		r_e1.x = p_e1.get_x();
		r_e1.y = p_e1.get_y();
	
	SDL_Rect r_e2 = p_e2.get_currentFrame();
		r_e2.x = p_e2.get_x();
		r_e2.y = p_e2.get_y();

	SDL_Rect minkowskiSum;
		minkowskiSum.w = 0.5f* (r_e1.w + r_e2.w);
		minkowskiSum.h = 0.5f* (r_e1.h + r_e2.h);
		minkowskiSum.x = (r_e1.x+r_e1.w/2) - (r_e2.x+r_e2.w/2);
		minkowskiSum.y = (r_e1.y+r_e1.h/2) - (r_e2.y+r_e2.h/2);
	

	if (abs(minkowskiSum.x) <= minkowskiSum.w && abs(minkowskiSum.y) <= minkowskiSum.h) {
		/* collision! */
		float wy = minkowskiSum.w * minkowskiSum.y;
		float hx = minkowskiSum.h * minkowskiSum.x;

		if (wy > hx){
			if (wy > -hx){
				/* collision at the top */
				return 1;
			} else {
				/* on the left */
				return 2;
			}
		} else {
			if (wy > -hx){
				/* on the right */
				return 3;
			}else{
				/* at the bottom */
				return 4;
			}
		}
	} else {
		return 0;
	}

}


Utils::Timer::Timer() : time(0){}

//p_t time to wait in ms
Utils::Timer::Timer(Uint32 p_t) : time(p_t){}

//Restart timer. time to wait in ms
void Utils::Timer::restart(Uint32 p_t){time = p_t; }

//Update the timer by dt ms
void Utils::Timer::update(Uint32 dt){
	if(dt <= time)
		time -= dt;
	else
		time = 0;
}

bool Utils::Timer::isDone(){
	return (time == 0);
}

