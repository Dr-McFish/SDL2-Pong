#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Entity.hpp"

#include "RenderWindow.hpp"

using std::cin;
using std::cout;
using std::endl;

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h) 
:window(NULL), renderer(NULL) {
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN | SDL_RENDERER_PRESENTVSYNC);
	if (window == NULL){
		cout << "Window failed to INIT. SDL_ERROR:" << SDL_GetError() << endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath) {
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);

	if (texture == NULL) {
		cout << "failed to load a texture. SDL ERROR: " <<SDL_GetError() << endl;
	}
	return texture;
}

void RenderWindow::cleanUp() {
	SDL_DestroyWindow(window);
}

void RenderWindow::clear() {
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& p_entity) {
	SDL_Rect src;
	src = p_entity.get_src();
	SDL_Rect dst;
	dst.x = p_entity.get_x() * renderScale;
	dst.y = p_entity.get_y() * renderScale;
	dst.w = p_entity.get_currentFrame().w * renderScale;
	dst.h = p_entity.get_currentFrame().h * renderScale;

	SDL_RenderCopy(renderer, p_entity.get_tex() , &src, &dst);
}


void RenderWindow::display() {
	SDL_RenderPresent(renderer);
}