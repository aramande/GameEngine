#ifndef CWING_H
#define CWING_H

#include <SDL.h>
#include <SDL_ttf.h>
namespace cwing{

	struct Globals{
		Globals();
		~Globals();
		SDL_Surface* screen;
		TTF_Font* font;
	};

	extern Globals sys;

} //cwing
#endif