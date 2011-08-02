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
	SDL_Surface* mainScreen = NULL;
	Window::Window(int width, int height, int depth){
		SDL_Init( SDL_INIT_EVERYTHING ); 
		TTF_Init();

		this->width = width; 
		this->height = height; 
		this->depth = depth;
		this->flags = SDL_HWSURFACE|SDL_RESIZABLE;
		
		mainScreen = SDL_SetVideoMode(width, height, depth, flags); 
		if (mainScreen == NULL) {
			throw sdl_error((std::string)"Video initialization failed: " + SDL_GetError());
		}
	}

	Window* Window::init(int width, int height, int depth){
		if(win == NULL) win = new Window(width, height, depth);
		return win;
	}

	void Window::kill(){
		if(win != NULL) delete win;
	}

	Window::~Window(){
		SDL_Quit();
	}

	void Window::resize(int w, int h){
		width = w;
		height = h;
		mainScreen = SDL_SetVideoMode(width, height, depth, flags); 
	}

	void Window::fullscreen(bool wantFullscreen){
		if(wantFullscreen){
			mainScreen = SDL_SetVideoMode(width, height, depth, flags | SDL_FULLSCREEN);
			flags = flags | SDL_FULLSCREEN;
		}
		else{
			mainScreen = SDL_SetVideoMode(width, height, depth, flags & ~SDL_FULLSCREEN);
			flags = flags & ~SDL_FULLSCREEN;
		}
	}
}
