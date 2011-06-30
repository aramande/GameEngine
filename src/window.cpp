/**
 * GameEngine - A regular application window
 * 
 * Author: Aramande <aramande@hackular.com>
 * File Created: Thu Jun 30 13:19:08 2011 UTC+2
 */

#include "window.h"
#include <string>
namespace engine{
	Window::Window(int width, int height, int depth){
		SDL_Init( SDL_INIT_EVERYTHING ); 
		screen = SDL_SetVideoMode(width, height, depth, SDL_SWSURFACE | SDL_RESIZABLE); 
		if (screen == NULL) {
			throw ((std::string)"Video initialization failed: " + SDL_GetError());
		}
		this->width = width; 
		this->height = height; 
		this->depth = depth;
		this->flags = SDL_HWSURFACE|SDL_RESIZABLE;
	}

	Window::~Window(){
		SDL_Quit();
	}

	void Window::fullscreen(bool wantFullscreen){
		if(wantFullscreen){
			screen = SDL_SetVideoMode(width, height, depth, flags | SDL_FULLSCREEN); 
		}
		else{
			screen = SDL_SetVideoMode(width, height, depth, flags & ~SDL_FULLSCREEN); 
		}
	}
}
