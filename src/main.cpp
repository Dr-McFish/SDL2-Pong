#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_Mixer.h>
#include <iostream>
#include <math.h>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "CoolObjects.hpp"
#include "Utils.hpp"
#include "KeyInput.hpp"
#include "Settings.hpp"

using std::cout;
using std::endl;


int main(int argc, char* args[]) {
	//Inititalization and debuging
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) > 0) {
		std::cout << "HEY, SDL_Init HAS FAILED! SDL_ERROR: " << SDL_GetError() << std::endl;
	}

	if (!(IMG_Init(IMG_INIT_PNG))){
		std::cout << "HEY, IMG_INIT_PNG HAS FAILED! SDL_ERROR: " << SDL_GetError() << std::endl;
	}
	
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0) 
		std::cout << "HEY, SDL_MIXER FAILED TO OPEN AUDIO! SDL_ERROR: " << Mix_GetError() << std::endl;
	//	

	//Instatioation
	RenderWindow window("GAME v1.0", 1280, 960); //subresolution 320 x 240
	SDL_Rect screenRect; //I wanted to mark this as const... it doesn't let me becase SDL_Rect has no constuctor to input x,y,w,h values
		screenRect.x = 0;
		screenRect.y = 0;
		screenRect.w = 320;
		screenRect.h = 240;
	SDL_Rect ballAreaRect;
		ballAreaRect.x = -20;
		ballAreaRect.y = 0;
		ballAreaRect.w = 320+40;
		ballAreaRect.h = 240;
	//
	const char* numsref = "0123456789";
	enum State {SPLASH, MAIN_MENUE, OPTIONS, GAME};
	State state = SPLASH;

	Settings settings;

	KeyInput input;
	

	
	SDL_Texture* ballTexture = window.loadTexture("res/images/pong_ball.png");
	SDL_Texture* lettersTexture = window.loadTexture("res/images/letters.png");
	SDL_Texture* fishLogoTexture = window.loadTexture("res/images/fishLogo.png");

	Mix_Chunk* pingSFX = Mix_LoadWAV("res/sfx/ping.wav");
	Mix_Chunk* splashSFX = Mix_LoadWAV("res/sfx/dramatic_noise.wav"); bool splashFlag = true;
	Mix_Chunk* clapSFX = Mix_LoadWAV("res/sfx/clap.wav");
	Mix_Chunk* winSFX = Mix_LoadWAV("res/sfx/win2.wav");
	Mix_Chunk* scoreSFX = Mix_LoadWAV("res/sfx/score.wav");
	Mix_Chunk* selectSFX = Mix_LoadWAV("res/sfx/select.wav");
	Mix_Chunk* countdownSFX = Mix_LoadWAV("res/sfx/countdown.wav");


	LetterSprite::spriteSheet = lettersTexture;
	Entity 	padleL(18, 120, ballTexture, 4 , 30),
			padleR(320-18, 120, ballTexture, 4 ,30),
			fishLogo(160 - (4*3*10 - 3)/2, 120, fishLogoTexture, 12*3, 15);
	#define LINE_NUM (int)(240/2.5f*4)
	Entity 	separatorLine[LINE_NUM];
	for (int i = 0; i < LINE_NUM; i++){
		separatorLine[i] = Entity(160, i*2.5f*4, ballTexture, 4, 4);
	}
	Ball 	ball(160, 120,  ballTexture, 6, 6);
	Score 	scoreR(160 - 50, 30, 7),
			scoreL(160 + 50, 30, 7);
	LetterSprite preGameCounter(160-15, 50, '0', 10);
	
	Text<10> splashText(160 + (12*3)/2, 120, 3, " DR MCFISH");
	Text<9> title(160, 50, 6, "SDL2 PONG");
	TextButton<9> menue1(160, 110 +4*6*0, 3, "P TO PLAY");
	TextButton<9> menue2(160, 110 +4*6*1, 3, "Q TO QUIT");
	Text<3> win(80, 240 -7*6, 7, "WIN");
	Text<5> serve(80+160, 240 - 6*4, 4, "SERVE");

	#define ENTITY_NUM 4
	Entity* enities[ENTITY_NUM] = { &padleL, &padleR, &ball , &preGameCounter };

	bool gameRunning = true;
	bool newGameFlag = true;
	SDL_Event event;
	
	
	Utils::Timer scoreTimeOutTimer;
	Utils::Timer preGameTimer(4000);
	Utils::Timer postGameTimer;
	Utils::Timer countdown(0);
	
	Utils::Timer collisionTimeOutTimer;
	//Game loop
	//Uint32 t = 0;
	Uint32 dt = 10;

	Uint32 currentTime = SDL_GetTicks() -1;
    Uint32 accumulator = 0;

	while(gameRunning){
		//FPS AND delta T calc
		Uint32 newTime = SDL_GetTicks();
		Uint32 frameTime = newTime - currentTime;
		currentTime = newTime;

		accumulator += frameTime;
		
		while (accumulator >= dt){
			//Game Logic goes here
			accumulator -=dt;

			input.update();
			while(SDL_PollEvent(&event)){
				if (event.type == SDL_QUIT){
					gameRunning = false;
				}
			}
			if(!gameRunning)
				break;


			switch (state) {
			case SPLASH:{
				preGameTimer.update(dt);
				if(preGameTimer.isDone()){
					state = MAIN_MENUE;
					//unload
				} else if(splashFlag && preGameTimer.time < 5000-1200){
					Mix_PlayChannel(-1, splashSFX, 0);
					splashFlag = false;
				}
				break;
			}case MAIN_MENUE:{
				//buttons Blah blah blah
				//menue1.update(input); menue2.update(input);

				if (input.getKeyDown(SDL_SCANCODE_P) /*|| menue1.isTriggered()*/) {
					state = GAME;
					preGameTimer.restart(3000);
					scoreL.set_score(0); scoreR.set_score(0);
					ball.reset();
					win.move(160+80, 240-7*6);
				} else if (input.getKeyDown(SDL_SCANCODE_Q) /*|| menue2.isTriggered()*/) {
					SDL_Quit();
					gameRunning = false;
				} //else if(input.getKeyDown(SDL_SCANCODE_Y)){
				//	menue1.move(200, 120);
				//}
				break;
			}case GAME:{
				preGameTimer.update(dt);
				scoreTimeOutTimer.update(dt);
				postGameTimer.update(dt);
				bool logicTimersDone = scoreTimeOutTimer.isDone() && preGameTimer.isDone() && postGameTimer.isDone();
				
				collisionTimeOutTimer.update(dt);
				countdown.update(dt);

				if(postGameTimer.isDone() && ball.isOut > 2 && !newGameFlag) {
					state = MAIN_MENUE;
					break;
				}

				if(!preGameTimer.isDone()){
					preGameCounter.set_letter(numsref[preGameTimer.time / 1000 +1]);
					if(countdown.isDone()){
						countdown.restart(1000);
						Mix_PlayChannel(-1, countdownSFX, 0);
					}
				} else {
					preGameCounter.set_letter(' ');
				}
				
				//paddle movement
				if (input.getKey(SDL_SCANCODE_W)) {
					padleL.move(0.0f, 3.5f);
				} else if (input.getKey(SDL_SCANCODE_S)) {
					padleL.move(0.0f, -3.5f);
				}

				if (input.getKey(SDL_SCANCODE_KP_8) || input.getKey(SDL_SCANCODE_LEFT) || input.getKey(SDL_SCANCODE_UP) || input.getKey(SDL_SCANCODE_O)) {
					padleR.move(0.0f, 3.5f);
				} else if (input.getKey(SDL_SCANCODE_KP_5)|| input.getKey(SDL_SCANCODE_RIGHT)|| input.getKey(SDL_SCANCODE_DOWN)|| input.getKey(SDL_SCANCODE_L)) {
					padleR.move(0.0f, -3.5f);
				} 


				//ball movement
				ball.integrate(dt/100.0f, ballAreaRect);
				if(ball.collision && (0 < ball.get_x() && ball.get_x() < 240) )
					Mix_PlayChannel(-1, clapSFX, 0);

				//collision with padles
				for (int i = 0; i < 2 && collisionTimeOutTimer.isDone() && logicTimersDone; i++)	{
					char colision = Utils::checkCollision(ball, *(enities[i]));
					if(colision){
						if((colision == 2 || colision == 3) || settings.corrnerBouncesAllowed){
							ball.reflect_x();
						}//float paddleC_x = enities[i]->get_x();

						float distanceFromPaddle = enities[i]->get_y() +(enities[i]->get_currentFrame().h/2) - (ball.get_y() + (ball.get_currentFrame().h/2));
						ball.set_velocity_y(distanceFromPaddle*1.2f);

						collisionTimeOutTimer.restart(120);
						Mix_PlayChannel(-1, clapSFX, 0);
						break;
					}
				}

				//Serving System
				if (ball.isOut == 1 && logicTimersDone) {
					ball.serveR();
					Mix_PlayChannel(-1, pingSFX, 0);
				} else if(ball.isOut == 2 && logicTimersDone){
					ball.serveL();
					Mix_PlayChannel(-1, pingSFX, 0);
				}

				//Scoring System
				if( -ball.get_currentFrame().w > ball.get_x()  && logicTimersDone){
					scoreL.inc_score();
					if(scoreL.get_score() == 10){
						//display win screen
						postGameTimer.restart(4000);
						Mix_PlayChannel(-1, winSFX, 0);
						ball.isOut = 4;
						newGameFlag= false;
						win.move(160+80, 240-7*6);
						break;
					} else {
						scoreTimeOutTimer.restart(1000);
						serve.move(80, 240 - 6*4);
						ball.isOut = 2;
						Mix_PlayChannel(-1, scoreSFX, 0);
					}
				} else if(  ball.get_x() > screenRect.w  && logicTimersDone){
					scoreR.inc_score();
					if(scoreR.get_score() == 10){
						//display win screen
						postGameTimer.restart(4000);
						Mix_PlayChannel(-1, winSFX, 0);
						ball.isOut = 3;
						newGameFlag= false;
						win.move(80, 240-7*6);
						break;
					} else {
						scoreTimeOutTimer.restart(1000);
						serve.move(160+80, 240 - 6*4);
						ball.isOut = 1;
						Mix_PlayChannel(-1, scoreSFX, 0);
					}
				}
				break;
			} default: {
				break;
			}
			}//endswitch
		
		}//endphysics

		//const float alpha = accumulator/dt;
		//rendering
		window.clear();
		switch(state) {
			case SPLASH:{
				window.render(fishLogo);
				splashText.renderText(window);
				break;
			}
			case MAIN_MENUE:{
				title.renderText(window);
				menue1.renderText(window);
				menue2.renderText(window);
				break;
			} case GAME: {
				for(int i=0; i < ENTITY_NUM; i++) {
					window.render(*enities[i]);
				}
				for (int i = 0; i < LINE_NUM; i++){
					window.render(separatorLine[i]);
				}
				scoreL.render(window);
				scoreR.render(window);
				if(ball.isOut > 2) {
					win.renderText(window);
				} else if(ball.isOut != 0){
					serve.renderText(window);
				}
				break;
			} default: {
				break;
			}
		}
		window.display();
	}
	Mix_CloseAudio();
	Mix_FreeChunk(pingSFX);
	Mix_FreeChunk(splashSFX);
	Mix_FreeChunk(clapSFX);
	Mix_FreeChunk(winSFX);
	Mix_FreeChunk(scoreSFX);
	Mix_FreeChunk(countdownSFX);
	Mix_FreeChunk(selectSFX);
	Mix_Quit();
	window.cleanUp();
	return 0;
	
}
