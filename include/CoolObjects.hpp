#pragma once
#include <iostream>
#include "Entity.hpp"
#include "Utils.hpp"
#include "RenderWindow.hpp"
#include "KeyInput.hpp"

class Ball : public Entity{
private:
	float velocity_x, velocity_y;
	const float defaultVelocity_x = -25;
	const float defaultVelocity_y = -8;
	const float normalTotalVelocity = 8.0f;
public:
	char isOut;
	bool collision;
	//using Entity::Entity; //inherit constructors
	Ball(float p_x, float p_y, SDL_Texture* p_tex, int p_tex_w, int p_tex_h);
	void velocityNormalize();
	void addVelocity(float p_vx, float p_vy);
	void reflect_x();
	void set_velocity(float p_vx, float p_vy);
	void set_velocity_y(float p_vy);
	void integrate(float p_delta_t, SDL_Rect& p_screen);
	void reset();
	void serveR();
	void serveL();
};


class LetterSprite : public Entity{
private:
	char letter;
	int fontsize;
public: 
	LetterSprite(float p_x, float p_y, char p_letter, int p_fontsize);
	LetterSprite();
	void update();
	void set_letter(char p_letter);
	static SDL_Texture* spriteSheet;
};
inline SDL_Texture* LetterSprite::spriteSheet;


class Score{
private:
	int score;
	LetterSprite digits[2];
	const char* numsref = "0123456789";
public:
	Score(float p_x, float p_y, int p_fontsize);
	int get_score();
	void set_score(int p_score);
	void inc_score();
	void update();
	void render(RenderWindow& window);
};

template <int LENGTH>
class Text{
private:
	int fontsize;
	LetterSprite spriteString[LENGTH];
	int edgeX, edgeY;
public:
	Text(float p_x, float p_y, int p_fontsize, const char* p_string) : fontsize(p_fontsize){
		fontsize = p_fontsize;
		edgeX = p_x - ((4*p_fontsize*LENGTH - 1*p_fontsize)/2);
		edgeY = p_y - fontsize*5/2;
		for (int i = 0; i < LENGTH; i++){
			spriteString[i] = LetterSprite(edgeX+4*p_fontsize*i, edgeY, p_string[i], p_fontsize);
		}
		
	}

	void renderText(RenderWindow& p_window){
		for (int i = 0; i < LENGTH; i++) {
			p_window.render(spriteString[i]);
		}
	}

	void move(int p_x, int p_y){
		edgeX = p_x - ((4*fontsize*LENGTH - 1*fontsize)/2);
		edgeY = p_y - fontsize*5/2;
		for (int i = 0; i < LENGTH; i++){
			spriteString[i].set_x(edgeX+4*fontsize*i);
			spriteString[i].set_y(edgeY);
		}		
	}

	void set_opacity(char p_){
		for (int i = 0; i < LENGTH; i++)
			spriteString[i].set_opacity(p_);
	}

	SDL_Rect get_rect(){
		SDL_Rect r_rect;
			r_rect.x = edgeX;
			r_rect.y = edgeY;
			r_rect.w = 4*fontsize*LENGTH -1*fontsize;
			r_rect.h = fontsize*5;
		return r_rect;
	}
};


template <int LENGTH>
class TextButton : public Text<9> {
private:
	bool _isTriggered;
	SDL_Rect collider;
public:
	TextButton(float p_x, float p_y, int p_fontsize, const char* p_string) : Text(p_x, p_y, p_fontsize, p_string), _isTriggered(false)
	{
		collider = this->get_rect();
	}

	void update(KeyInput& p_inp){
		if(collider.x < p_inp.get_Mouse_x() && p_inp.get_Mouse_x() < collider.x + collider.w && collider.y < p_inp.get_Mouse_y() && p_inp.get_Mouse_y() < collider.y+ collider.h){
			this->set_opacity(0.75f*255);
			_isTriggered = p_inp.getMouseDown(SDL_BUTTON(SDL_BUTTON_LEFT));
		} else {
			this->set_opacity(SDL_ALPHA_OPAQUE);
		}
	}

	bool isTriggered(){return _isTriggered;}
};