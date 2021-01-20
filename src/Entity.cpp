#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <iostream>

#include "Entity.hpp"

// using std::cout;
// using std::endl;



Entity::Entity(float p_x, float p_y, SDL_Texture* p_tex, int p_tex_w, int p_tex_h, bool isCentered) 
:x(p_x), y(p_y), tex(p_tex) {

	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = p_tex_w;
	currentFrame.h = p_tex_h;

	src = currentFrame;
}

Entity::Entity(float p_x, float p_y, SDL_Texture* p_tex, int p_tex_w, int p_tex_h) 
: Entity(p_x - (p_tex_w/2), p_y - (p_tex_h/2), p_tex, p_tex_w, p_tex_h, false){}

Entity::Entity() : Entity(0, 0, NULL, 1, 1, false){}

//GETTERS
float Entity::get_x(){return x;}
float Entity::get_y(){return y;}
void Entity::set_x(float p_x){x = p_x;} 
void Entity::set_y(float p_y){y = p_y;}
SDL_Texture* Entity::get_tex(){return tex;}
SDL_Rect& Entity::get_currentFrame(){return currentFrame;}
SDL_Rect& Entity::get_src(){return src;}

void Entity::move(float p_x, float p_y){
	x +=p_x;
	y -=p_y;
}

void Entity::set_opacity(char p_){
	SDL_SetTextureAlphaMod(tex, p_);
}