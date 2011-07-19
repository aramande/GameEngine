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
	Window* Window::win = NULL;
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

	Window* Window::init(int width, int height, int depth){
		if(win == NULL) win = new Window(width, height, depth);
		return win;
	}

	Window::~Window(){
		SDL_Quit();
	}

	void Window::resize(int w, int h){
		width = w;
		height = h;
		screen = SDL_SetVideoMode(width, height, depth, flags); 
	}

	void Window::fullscreen(bool wantFullscreen){
		if(wantFullscreen){
			screen = SDL_SetVideoMode(width, height, depth, flags | SDL_FULLSCREEN);
			flags = flags | SDL_FULLSCREEN;
		}
		else{
			screen = SDL_SetVideoMode(width, height, depth, flags & ~SDL_FULLSCREEN);
			flags = flags & ~SDL_FULLSCREEN;
		}
	}
}
