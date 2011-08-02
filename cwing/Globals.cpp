#include "Globals.h"
#include "CwingError.h"
#include <SDL.h>

namespace cwing{

	Globals sys;


	Globals::Globals(){
		if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
			throw CwingError(SDL_GetError());
		screen = SDL_SetVideoMode(600,500,32,
			SDL_SWSURFACE | SDL_DOUBLEBUF);
		TTF_Init();
		font = TTF_OpenFont("c:/WINDOWS/Fonts/timesbd.ttf",18);
	}


	Globals::~Globals(){
		TTF_CloseFont(font);
		TTF_Quit();
		SDL_Quit();
	}
} // cwing