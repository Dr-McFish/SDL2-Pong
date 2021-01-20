#include <iostream>
#include "Entity.hpp"
#include "Utils.hpp"
#include "RenderWindow.hpp"

#include "CoolObjects.hpp"

Ball::Ball(float p_x, float p_y, SDL_Texture* p_tex, int p_tex_w, int p_tex_h) : Entity(p_x, p_y, p_tex, p_tex_w, p_tex_h){isOut = true;}

void Ball::velocityNormalize(){
	// float totalVelocity = std::sqrt((velocity_x*velocity_x) + (velocity_y*velocity_y)); 
	// velocity_x *= totalVelocity/normalTotalVelocity;
	// velocity_y *= totalVelocity/normalTotalVelocity;
}

void Ball::addVelocity(float p_vx, float p_vy){
	velocity_x += p_vx;
	velocity_y += p_vy;
}

void Ball::reflect_x(){
	velocity_x *= -1;
}

void Ball::set_velocity_y(float p_vy){
	velocity_y = p_vy;
}

void Ball::set_velocity(float p_vx, float p_vy){
	velocity_x = p_vx;
	velocity_y = p_vy;
}

void Ball::integrate(float p_delta_t, SDL_Rect& p_screen){
	//Move the ball according to it's velocity
	this->move(velocity_x*p_delta_t, velocity_y*p_delta_t);

	//bounce the ball of the top and bottom of the screen
	if( !(p_screen.y < y && y < p_screen.y + p_screen.h - currentFrame.h) ){
		velocity_y *= -1;
		collision = true;
	} else
		collision = false;
	//Utils::clampIn(p_screen, this);	
}

void Ball::serveL(){
	x = 160; y = 120;
	velocity_x = defaultVelocity_x;
	velocity_y = defaultVelocity_y;
	isOut = false;
}
void Ball::serveR(){
	x = 160; y = 120;
	velocity_x = -defaultVelocity_x;
	velocity_y = defaultVelocity_y;
	isOut = false;
}

void Ball::reset(){
	x = 160 - (currentFrame.w/2); y = 120 - (currentFrame.h/2);
	velocity_x = 0;
	velocity_y = 0;
	isOut = 1;
}




Score::Score(float p_x, float p_y, int p_fontsize) 
	: score(0) {
	for(int i =0; i < 2; i++){
		digits[i] = LetterSprite(p_x - 4*p_fontsize*i, p_y - ((p_fontsize*5)/2), '0', p_fontsize);
	}
}

int Score::get_score(){return score;}
void Score::set_score(int p_score){
	score = p_score;
	update();
}
void Score::inc_score(){
	score++;
	update();
}

void Score::update(){
	if(score < 100){
		digits[0].set_letter(numsref[score % 10]);
		digits[1].set_letter(numsref[(score/10 % 100)]);
	}
}

void Score::render(RenderWindow& window){
	for(int i =0; i < 2; i++){
		window.render(digits[i]);
	}
}





LetterSprite::LetterSprite(float p_x, float p_y, char p_letter, int p_fontsize) :Entity(p_x, p_y, this->spriteSheet, 3*p_fontsize, 5*p_fontsize, false), letter(p_letter), fontsize(p_fontsize){
	update();
	src.w = 3;
	src.h = 5;
}

LetterSprite::LetterSprite() :Entity(0, 0, NULL, 3, 5, false), letter('A'), fontsize(1){
	update();
	src.w = 3;
	src.h = 5;
}


void LetterSprite::update(){
	if(letter >= 65){
		src.x = ((letter - 65) % 9)* 4;
		src.y = ((letter - 65) / 9)* 6;
	} else if(letter >= 48){
		src.x = ((letter - 48 + 26) % 9)* 4;
		src.y = ((letter - 48 + 26) / 9)* 6;
	} else if(letter >= 32){
		src.x = 0;
		src.y = 4*6;
	}
}

void LetterSprite::set_letter(char p_letter){letter = p_letter; update();}





