#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Entity{
public:
	Entity(float p_x, float p_y, SDL_Texture* p_tex, int p_tex_w, int p_tex_h, bool isCentered);
	Entity(float p_x, float p_y, SDL_Texture* p_tex, int p_tex_w, int p_tex_h);
	Entity();
	float get_x(), get_y();
	void set_x(float p_x), set_y(float p_y);
	void move(float p_x, float p_y);
	void set_opacity(char p_);
	SDL_Texture* get_tex();
	SDL_Rect& get_currentFrame();
	SDL_Rect& get_src();
protected:
	float x, y;
	SDL_Texture* tex;
	SDL_Rect currentFrame;
	SDL_Rect src;
};