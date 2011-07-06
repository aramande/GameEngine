/**
 * GameEngine - A regular application window
 * 
 * Author: Aramande <aramande@hackular.com>
 * File Created: Thu Jun 30 13:19:08 2011 UTC+2
 */

#include "window.h"
#include "sdlerror.h"
#include <string>

namespace engine{
	Window::Window(int width, int height, int depth){
		SDL_Init( SDL_INIT_EVERYTHING ); 
		
		this->width = width; 
		this->height = height; 
		this->depth = depth;
		this->flags = SDL_HWSURFACE|SDL_RESIZABLE;
		
		screen = SDL_SetVideoMode(width, height, depth, flags); 
		if (screen == NULL) {
			throw sdl_error((std::string)"Video initialization failed: " + SDL_GetError());
		}
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
